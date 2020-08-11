/* primtab0.c */
/* Copyright (c) 2020 J. M. Spivey */

#include "obx.h"
#include <ctype.h>
#include <unistd.h>

typedef int type_C, type_I;
typedef longint type_L;
typedef float type_F;
typedef double type_D;
typedef void *type_P, *type_Q, *type_X;
typedef void type_V;

void P_xmain_exit(value *bp) {
     xmain_exit(bp[HEAD].i);
}

void NEW(value *bp);
void NEWFLEX(value *bp);
void COMPARE(value *bp);

void P_toupper(value *bp) {
     ob_res.i = toupper(align_byte(bp[HEAD].i));
}

void COPY(value *bp);
void FLEXASSIGN(value *bp);
void sys_move(value *bp);
void sys_liberror(value *bp);

void P_load_lib(value *bp) {
     load_lib((char *) pointer(bp[HEAD]));
}

void gc_collect(value *bp);

void P_gc_debug(value *bp) {
     gc_debug((char *) pointer(bp[HEAD]));
}

void P_gc_heap_size(value *bp) {
     ob_res.i = gc_heap_size();
}

void P_fopen(value *bp) {
     put_long(&ob_res,(ptrtype) fopen((char *) pointer(bp[HEAD]),
                                      (char *) pointer(bp[HEAD+2])));
}

void P_fclose(value *bp) {
     fclose(ptrcast(void, get_long(&bp[HEAD]))); 
}

void P_fflush(value *bp) {
     fflush(ptrcast(void, get_long(&bp[HEAD]))); 
}

void P_obgetc(value *bp) {
     ob_res.i = getc(ptrcast(void, get_long(&bp[HEAD]))); 
}

void P_ungetc(value *bp) {
     ungetc(align_byte(bp[HEAD].i),
             ptrcast(void, get_long(&bp[HEAD+1]))); 
}

void P_fputc(value *bp) {
     fputc(align_byte(bp[HEAD].i),
            ptrcast(void, get_long(&bp[HEAD+1]))); 
}

void P_fseek(value *bp) {
     fseek(ptrcast(void, get_long(&bp[HEAD])),
            bp[HEAD+2].i, bp[HEAD+3].i); 
}

void P_ftell(value *bp) {
     ob_res.i = ftell(ptrcast(void, get_long(&bp[HEAD]))); 
}

void P_fread(value *bp) {
     ob_res.i = fread(pointer(bp[HEAD]), bp[HEAD+2].i,
                       bp[HEAD+3].i,
                       ptrcast(void, get_long(&bp[HEAD+4]))); 
}

void P_fwrite(value *bp) {
     fwrite(pointer(bp[HEAD]), bp[HEAD+2].i, bp[HEAD+3].i,
             ptrcast(void, get_long(&bp[HEAD+4]))); 
}

void P_FmtInt(value *bp) {
     void FmtInt(void *, int, int);
     FmtInt(ptrcast(void, get_long(&bp[HEAD])),
             bp[HEAD+2].i, bp[HEAD+3].i); 
}

void P_FmtLong(value *bp) {
     void FmtLong(void *, longint, int);
     FmtLong(ptrcast(void, get_long(&bp[HEAD])),
              get_long(&bp[HEAD+2]), bp[HEAD+4].i); 
}

void P_FmtReal(value *bp) {
     void FmtReal(void *, float);
     FmtReal(ptrcast(void, get_long(&bp[HEAD])), bp[HEAD+2].f); 
}

void P_FmtLongReal(value *bp) {
     void FmtLongReal(void *, double);
     FmtLongReal(ptrcast(void, get_long(&bp[HEAD])),
                  get_double(&bp[HEAD+2])); 
}

void P_FmtFixed(value *bp) {
     void FmtFixed(void *, double, int, int);
     FmtFixed(ptrcast(void, get_long(&bp[HEAD])),
               get_double(&bp[HEAD+2]),
               bp[HEAD+4].i, bp[HEAD+5].i); 
}

void P_FmtString(value *bp) {
     void FmtString(void *, void *, int);
     FmtString(ptrcast(void, get_long(&bp[HEAD])),
                pointer(bp[HEAD+2]), bp[HEAD+4].i); 
}

void P_InitFiles(value *bp) {
     void InitFiles(void *, void *, void *);
     InitFiles(pointer(bp[HEAD]), pointer(bp[HEAD+1]),
                pointer(bp[HEAD+2])); 
}

void P_atoi(value *bp) {
     ob_res.i = atoi((char *) pointer(bp[HEAD])); 
}

void P_atof(value *bp) {
     put_double(&ob_res, atof((char *) pointer(bp[HEAD]))); 
}

void GetArg(value *bp);

void GetEnv(value *bp);

void P_GetArgc(value *bp) {
     int GetArgc(void); ob_res.i = GetArgc();
}

void COMPARE(value *bp);

void P_unlink(value *bp) {
     ob_res.i = unlink((char *) pointer(bp[HEAD]));
}

struct primdef primtab[] = {
     { "P_xmain_exit", P_xmain_exit },
     { "NEW", NEW },
     { "NEWFLEX", NEWFLEX },
     { "COMPARE", COMPARE },
     { "P_toupper", P_toupper },
     { "COPY", COPY },
     { "FLEXASSIGN", FLEXASSIGN },
     { "sys_move", sys_move },
     { "sys_liberror", sys_liberror },
     { "P_load_lib", P_load_lib },
     { "gc_collect", gc_collect },
     { "P_gc_debug", P_gc_debug },
     { "P_gc_heap_size", P_gc_heap_size },
     { "P_fopen", P_fopen },
     { "P_fclose", P_fclose },
     { "P_fflush", P_fflush },
     { "P_obgetc", P_obgetc },
     { "P_ungetc", P_ungetc },
     { "P_fputc", P_fputc },
     { "P_fseek", P_fseek },
     { "P_ftell", P_ftell },
     { "P_fread", P_fread },
     { "P_fwrite", P_fwrite },
     { "P_FmtInt", P_FmtInt },
     { "P_FmtLong", P_FmtLong },
     { "P_FmtReal", P_FmtReal },
     { "P_FmtLongReal", P_FmtLongReal },
     { "P_FmtFixed", P_FmtFixed },
     { "P_FmtString", P_FmtString },
     { "P_InitFiles", P_InitFiles },
     { "P_atoi", P_atoi },
     { "P_atof", P_atof },
     { "GetArg", GetArg },
     { "GetEnv", GetEnv },
     { "P_GetArgc", P_GetArgc },
     { "COMPARE", COMPARE },
     { "P_unlink", P_unlink },
     { NULL, NULL }
};
