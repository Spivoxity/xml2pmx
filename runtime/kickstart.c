/*
 * kickstart.c
 * Copyright (c) 2006--2020 J. M. Spivey
 * All rights reserved
 */

#include "obx.h"
#include "keiko.h"
#include "exec.h"

extern const unsigned preload_seglen[NSEGS];
extern const uchar preload_imem[];
extern const unsigned preload_dmem[];
extern const uchar preload_reloc[];
extern const unsigned preload_entry, preload_gcmap;
extern const unsigned preload_nprocs;
extern const struct pre_proc { char *name; unsigned addr; } preload_syms[];

void put4(uchar *buf, int x) {
     buf[0] = x;
     buf[1] = x >> 8;
     buf[2] = x >> 16;
     buf[3] = x >> 24;
}

/* relocate -- read relocation data */
static void relocate(int size) {
     int m, i;
     unsigned *p;

     for (i = 0; i < size; i += WORD_SIZE) {
          int rbits = reloc_bits(preload_reloc, i/WORD_SIZE);

#ifdef DEBUG
          if (dflag > 3)
               printf("Reloc %d %d\n", i, rbits);
#endif

          p = (unsigned *) &dmem[i];

          switch (rbits) {
          case R_NONE:
               put4((uchar *) p, *p);
               break;
          case R_WORD:
               break;
          case R_ADDR:
               m = *p;
               if ((m & IBIT) == 0)
                    *p = address(dmem + m);
               else
                    *p = codeaddr(imem + (m & ~IBIT));
               break;
          case R_SUBR:
               switch (*p) {
               case INTERP: *p = interpreter; break;
               case DLTRAP: *p = dyntrap; break;
               default:
                    panic("bad subr code %x\n", *p);
               }
               break;
          }
     }
}
	       
/* read_symbols -- read symbol table */
static void read_symbols(void) {
     int i;

     proctab = (proc *) scratch_alloc(nprocs * sizeof(proc));

     for (i = 0; i < nprocs; i++) {
          const struct pre_proc *p = &preload_syms[i];
          proctab[i] = make_proc(p->name, dmem + p->addr);
     }
}

/* load_image -- unpack preloaded file of object code */
void load_image(void) {
     int i;
     int seglen[NSEGS];

     /* Decode the other data */
     for (i = 0; i < NSEGS; i++)
	  seglen[i] = preload_seglen[i];

     code_size = seglen[S_CODE];
     stack_size = seglen[S_STACK];

     nmods = 0;
     nprocs = preload_nprocs;
     nsyms = nprocs;

     /* Load the code */
     imem = (uchar *) preload_imem;

     /* Load and relocate the data */
     dmem = (uchar *) scratch_alloc(seglen[S_DATA]+seglen[S_BSS]);
     memcpy(dmem, preload_dmem, seglen[S_DATA]);
     relocate(seglen[S_DATA]);
     memset(dmem+seglen[S_DATA], 0, seglen[S_BSS]);

     /* Allocate stack */
     stack = (uchar *) scratch_alloc(stack_size);

     /* Save the entry point, pointer map and library path */
     entry = (value *) &dmem[preload_entry];
     gcmap = (value *) &dmem[preload_gcmap];

     /* Read the symbols */
     if (nsyms > 0) read_symbols();
}
