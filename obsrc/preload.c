/*
 * preload.c
 * Copyright (c) 2006--2020 J. M. Spivey
 * All rights reserved
 */

#include "obx.h"
#include "keiko.h"
#include "exec.h"
#include <stdlib.h>

#define scratch_alloc(size) malloc(size);

void panic(const char *msg, ...) {
     va_list va;

     mybool bug = FALSE;

     if (*msg == '*') {
	  bug = TRUE; msg++;
     }

     fflush(stdout);
     fprintf(stderr, "Fatal error: ");
     va_start(va, msg);
     vfprintf(stderr, msg, va);
     va_end(va);
     fprintf(stderr, "\n");
     if (bug)
	  fprintf(stderr, "Please report bugs to %s\n", PACKAGE_BUGREPORT);
     fflush(stderr);
     exit(1);
}

int stack_size;
int nsyms;
uchar *dmem;
uchar *imem;
int code_size;
int nprocs;

static FILE *binfp;

static int binread(void *buf, int size) {
     return fread(buf, 1, size, binfp);
}

static int bingetc(void) {
     char buf[1];
     if (binread(buf, 1) == 0) return EOF;
     return buf[0];
}

/* read_string -- input a null-terminated string, allocate space dynamically */
static char *read_string() {
     int n = 0;
     int c;
     char *p;
     char buf[256];
     
     do {
	  c = bingetc();
	  if (c == EOF) panic("*unexpected EOF");
	  buf[n++] = c;
     } while (c != '\0');

     p = (char *) scratch_alloc(n);
     strcpy(p, buf);
     return p;
}

/* get_int -- get a 4-byte value in portable byte order */
static int get_int(uchar *p) {
     return (p[3]<<24) + (p[2]<<16) + (p[1]<<8) + p[0];
}

/* read_int -- input a 4-byte value in portable byte order */
static int read_int() {
     uchar buf[4];
     binread(buf, 4);
     return get_int(buf);
}

/* read_symbols -- read symbol table */
static void read_symbols(void) {
     unsigned addr;
     int i, np = 0;
	  
     printf("const struct _proc preload_syms[] = {\n");

     for (i = 0; i < nsyms; i++) {
	  int kind = read_int();
	  char *name = read_string(); 

	  switch (kind) {
	  case X_MODULE:
	       read_int(); read_int(); read_int();
	       break;

	  case X_PROC:
	       addr = read_int(); 
	       printf("     { \"%s\", %u },\n", name, addr);
               np++;
	       break;
		    
	  case X_DATA:
	  case X_LINE:
	       read_int(); 
	       break;

	  default:
	       panic("*bad symbol %s", name);
	  }
     }

     printf("};\n");

     if (np != nprocs)
          panic("Wrong number of procs");
}

void put_bytes(char *name, uchar *data, unsigned len) {
     int i, j;
     
     printf("const unsigned char %s[] = {\n", name);
     for (i = 0; i < len; i += 8) {
          printf("    ");
          for (j = 0; j < 8 && i+j < len; j++)
               printf(" %#x,", data[i+j]);
          printf("\n");
     }
     printf("};\n\n");
}
 
void put_words(char *name, unsigned *data, unsigned len) {
     int i, j;
     
     /* The words are read in portable byte-order to write
        them out as integer constants.  A big-endian host
        will need to swap bytes in any word that represents
        character data */

     printf("const unsigned %s[] = {\n", name);
     for (i = 0; i < len; i += 4) {
          printf("    ");
          for (j = 0; j < 4 && i+j < len; j++)
               printf(" %#x,", get_int((uchar *) &data[i+j]));
          printf("\n");
     }
     printf("};\n\n");
}

/* load_file -- load a file of object code */
void load_file(FILE *bfp) {
     trailer t;
     int i, nread, start, rbytes;
     int seglen[NSEGS];
     uchar *rmem;

     /* Get trailer */
     fseek(bfp, - (long) sizeof(trailer), SEEK_END);
     nread = fread(&t, 1, sizeof(trailer), bfp);
     if (nread != sizeof(trailer)) panic("couldn't read trailer");

     /* Check magic numbers */
     if (nread < sizeof(trailer))
	  panic("couldn't read trailer");
     if (strncmp((char *) t.magic, MAGIC, 4) != 0)
	  panic("bad magic number\n%s",
		"[The program you are running is not a valid"
		" Oberon bytecode file]");
     if (get_int(t.sig) != SIG)
	  panic("bad signature %#0.8x\n%s\n%s", get_int(t.sig),
		"[Although this appears to be an Oberon bytecode file,",
		"  it needs a different version of the runtime system]");

     /* Decode the other data */
     for (i = 0; i < NSEGS; i++)
	  seglen[i] = get_int(t.segment[i]);

     code_size = seglen[S_CODE];
     stack_size = seglen[S_STACK];

     nsyms = get_int(t.nsyms);
     nprocs = get_int(t.nprocs);
     start = get_int(t.start);

     printf("#include \"obx.h\"\n\n");

     printf("const unsigned preload_seglen[] = {\n");
     printf("    ");
     for (i = 0; i < NSEGS; i++) printf(" %u,", seglen[i]);
     printf("\n");
     printf("};\n\n");

     fseek(bfp, start, SEEK_END);
     binfp = bfp;

     /* Load the code */
     imem = (uchar *) scratch_alloc(seglen[S_CODE]);
     binread(imem, seglen[S_CODE]);
     put_bytes("preload_imem", imem, seglen[S_CODE]);

     /* Load and relocate the data */
     dmem = (uchar *) scratch_alloc(seglen[S_DATA]);
     binread(dmem, seglen[S_DATA]);
     put_words("preload_dmem", (unsigned *) dmem, seglen[S_DATA]/4);

     rbytes = (seglen[S_DATA]/WORD_SIZE+CODES_PER_BYTE-1)/CODES_PER_BYTE;
     rmem = (uchar *) scratch_alloc(rbytes);
     binread(rmem, rbytes);
     put_bytes("preload_reloc", rmem, rbytes);

     /* Save the entry point and pointer map */
     printf("const unsigned preload_entry = %u;\n", get_int(t.entry));
     printf("const unsigned preload_gcmap = %u;\n\n", get_int(t.gcmap));

     /* Read the symbols */
     printf("const unsigned preload_nprocs = %u;\n\n", nprocs);
     read_symbols();
}

int main(int argc, char *argv[]) {
     FILE *fp;

     if (argc < 2) {
          fprintf(stderr, "Usage: preload file.x\n");
          exit(2);
     }
     
     fp = fopen(argv[1], "rb");
     if (fp == NULL) {
          fprintf(stderr, "preload: Can't read %s\n", argv[1]);
          exit(1);
     }
     
     load_file(fp);
     return 0;
}
