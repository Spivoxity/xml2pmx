/* Generated by makestubs */

#include "primtab.h"

#define PRIMS(direct, indirect, wrapper) \
     wrapper(xmain_exit, V, I) \
     direct(NEW) \
     direct(NEWFLEX) \
     direct(COMPARE) \
     wrapper(toupper, C, C) \
     direct(COPY) \
     direct(FLEXASSIGN) \
     direct(sys_move) \
     direct(sys_liberror) \
     wrapper(load_lib, V, X) \
     direct(gc_collect) \
     wrapper(gc_debug, V, X) \
     wrapper(gc_heap_size, I) \
     wrapper(fopen, Q, X, X) \
     wrapper(fdopen, Q, I, X) \
     wrapper(fclose, V, Q) \
     wrapper(fflush, V, Q) \
     wrapper(obgetc, I, Q) \
     wrapper(ungetc, V, C, Q) \
     wrapper(fputc, V, C, Q) \
     wrapper(fseek, V, Q, I, I) \
     wrapper(ftell, I, Q) \
     wrapper(fread, I, X, I, I, Q) \
     wrapper(fwrite, V, X, I, I, Q) \
     indirect(FmtInt, V, Q, I, I) \
     indirect(FmtLong, V, Q, L, I) \
     indirect(FmtReal, V, Q, F) \
     indirect(FmtLongReal, V, Q, D) \
     indirect(FmtFixed, V, Q, D, I, I) \
     indirect(FmtString, V, Q, X, I) \
     indirect(InitFiles, V, P, P, P) \
     wrapper(atoi, I, X) \
     wrapper(atoll, L, X) \
     wrapper(atof, D, X) \
     direct(GetArg) \
     direct(GetEnv) \
     indirect(GetArgc, I) \
     direct(COMPARE)

PRIMTAB(PRIMS)