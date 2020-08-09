/*
 * xmain.c
 * 
 * This file is part of the Oxford Oberon-2 compiler
 * Copyright (c) 2006--2016 J. M. Spivey
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define main xmain

#define EXTERN
#include "obx.h"
#include "keiko.h"
#include "exec.h"

#ifdef JIT
#include "vm.h"
#ifdef DEBUG
#define JTEST 1
#endif
#endif

#ifdef PROFILE
#define MYNAME "profiler"
#else
#ifdef OBXDEB
#define MYNAME "debugging monitor"
#else
#define MYNAME "runtime system"
#endif
#endif

const char *version = 
"Oxford Oberon-2 " MYNAME " version " PACKAGE_VERSION " [build " REVID "]"
#ifdef JIT
		       " (JIT)"
#else
		       ""
#endif
#ifdef DEBUG
		       " (debug)"
#else
		       ""
#endif
     ;
const char *copyright = "Copyright (C) 1999--2012 J. M. Spivey";

extern int vm_debug;

/* Helper functions for the loader */

module make_module(char *name, uchar *addr, int chksum, int nlines) {
     module m = (module) scratch_alloc(sizeof(struct _module));
     m->m_name = name;
     m->m_addr = addr;
#ifdef PROFILE
     m->m_nlines = nlines;
     m->m_lcount = NULL;
     if (lflag && nlines > 0) {
	  m->m_lcount = 
	       (unsigned *) scratch_alloc(nlines * sizeof(unsigned));
	  memset(m->m_lcount, 0, nlines * sizeof(int));
     }
#endif
#ifdef OBXDEB
     debug_message("module %s %#x", name, chksum);
#endif
     return m;
}

proc make_proc(char *name, unsigned addr) {
     proc p = (proc) scratch_alloc(sizeof(struct _proc));
     p->p_name = name;
     p->p_addr = addr;
#ifdef PROFILE
     p->p_calls = p->p_rec = p->p_self = p->p_child = 0;
     p->p_parents = p->p_children = NULL;
#endif
#ifdef OBXDEB
     debug_message("proc %s %#x %#x %d", name, address(addr), 
		   p->p_addr[CP_CODE].a, p->p_addr[CP_SIZE].i);
#endif
     return p;
}

void make_symbol(const char *kind, char *name, uchar *addr) {
#ifdef OBXDEB
     debug_message("%s %s %#x", kind, name, address(addr));
#endif
}

/* Runtime errors */

#ifndef OBXDEB
#define TOP 5			/* Number of frames shown at top and bottom */
#define BOT 5
#define GAP 10			/* Don't omit less than this many frames */
#define NBUF (BOT+GAP-1)

static void backtrace(value *bp) {
     value *fp = bp, *cp = valptr(bp[CP]);
     proc p = find_proc(cp);
     int n, j;
     proc fbuf[NBUF];
     
     fprintf(stderr, "In procedure %s\n", p->p_name);

     /* Chain down the stack, printing the first TOP frames,
	and saving the last NBUF in a circular buffer. */
     for (n = 0;; n++) {
	  /* Each frame contains the cp and bp of its caller */
	  fp = valptr(fp[BP]);	/* Base pointer of next frame */
	  if (fp == NULL) break;
	  cp = valptr(fp[CP]);	/* Constant pool of next frame */
	  fbuf[n%NBUF] = p = find_proc(cp);
	  if (n < TOP)
	       fprintf(stderr, "   called from %s\n", p->p_name);
     }

     /* Now the last NBUF frames are f(n-NBUF), ..., f(n-1)
	where f(i) = fbuf[i%NBUF] -- unless there are fewer
	then NBUF frames in all. */

     if (n < TOP+GAP+BOT) 
	  /* Print the n-TOP frames not printed already */
	  j = TOP;
     else {
	  /* Omit n-(TOP+BOT) frames (at least GAP) and print the 
	     last BOT frames */
	  fprintf(stderr, "   ... %d intervening frames omitted ...\n", 
		  n-(TOP+BOT));
	  j = n-BOT;
     }

     /* Print frames j, ..., n-1 */
     for (; j < n; j++)
	  fprintf(stderr, "   called from %s\n", fbuf[j%NBUF]->p_name);
}
#endif

static const char *message(int code) {
     switch (code) {
     case E_CAST:
	  return "dynamic type error in cast";
     case E_ASSIGN:
	  return "dynamic type error in record assignment";
     case E_CASE:
	  return "no matching label in CASE statement";
     case E_WITH:
	  return "no matching type guard in WITH statement";
     case E_ASSERT:
	  return "assertion failed (%d)";
     case E_RETURN:
	  return "function failed to return a result";
     case E_BOUND:
	  return "array bound error";
     case E_NULL:
	  return "null pointer error";
     case E_DIV:
	  return "DIV or MOD by zero";
     case E_FDIV:
	  return "division by zero";
     case E_STACK:
	  return "stack overflow";
     case E_GLOB:
	  return "assignment of local procedure";
     default:
	  return "the impossible has happened";
     }
}

/* error_stop -- runtime error with explicit message text */
void error_stop(const char *msg, int line, value *bp, uchar *pc) {
#ifdef OBXDEB
     value *cp = valptr(bp[CP]);
     char buf[256];
     sprintf(buf, msg, ob_res.i);
     debug_break(cp, bp, pc, "error %d %s", line, buf);
#else
     fprintf(stderr, "Runtime error: ");
     fprintf(stderr, msg, ob_res.i);
     if (line > 0) fprintf(stderr, " on line %d\n", line);
     fprintf(stderr, "\n");
     fflush(stderr);

     if (nprocs == 0)
	  fprintf(stderr, "(No debugging information available)\n");
     else if (bp != NULL)
	  backtrace(bp);

     fflush(stderr);
#endif

     exit(2);
}

/* runtime_error -- report a runtime error */
void runtime_error(int m, int line, value *bp, uchar *pc) {
     error_stop(message(m), line, bp, pc);
}

/* rterror -- simple version of runtime_error for JIT */
void rterror(int num, int line, value *bp) {
     runtime_error(num, line, bp, NULL);
}

/* stkoflo -- stack overflow handler for JIT */
void stkoflo(value *bp) {
     runtime_error(E_STACK, 0, bp, NULL);
}


/* Startup */

static void run(value *prog) {
     value *sp;

     /* Allow 32-word safety margin (for tracing) */
     sp = (value *) (stack + stack_size) - 32; 

     sp -= HEAD; 
     sp[BP].a = address(NULL); 
     sp[PC].a = address(NULL); 
     sp[CP].a = address(prog);
     primcall(prog, sp);
}

#define argc saved_argc
#define argv saved_argv

static char *progname;
#ifdef PROFILE
static char *profout;
static const char *dumpname = "obprof.out";
#endif

#ifdef JTEST
static mybool tflag = 0;
#endif

#ifdef PROFILE
static void dump_lcounts(void) {
     FILE *fp = fopen(dumpname, "w");
     if (fp == NULL) {
	  fprintf(stderr, "%s: cannot write\n", dumpname);
	  exit(1);
     }

     for (int m = 0; m < nmods; m++)
	  for (int n = 1; n <= modtab[m]->m_nlines; n++)
	       if (modtab[m]->m_lcount[n-1] > 0)
		    fprintf(fp, "%s %d %u\n", modtab[m]->m_name, n, 
			    modtab[m]->m_lcount[n-1]);

     fclose(fp);
}

static void print_profile(void) {
     FILE *fp = stderr;

     if (profout != NULL) {
	  fp = fopen(profout, "w");
	  if (fp == NULL) {
	       fprintf(stderr, "%s: cannot write\n", profout);
	       exit(1);
	  }

	  fprintf(fp, "Command line:\n\n");
	  fprintf(fp, "  %s", saved_argv[0]);
	  for (int i = 1; i < saved_argc; i++)
	       fprintf(fp, " %s", saved_argv[i]);
	  fprintf(fp, "\n\n");
     }

     profile(fp);

     if (fp != stderr) fclose(fp);
}
#endif

#ifdef JTEST
static void jit_test(void) {
     dflag = vm_debug = 2; vm_aflag = 1;
     if (nmods < 2) panic("Can't find main module");
     module m = modtab[nmods-2];
     for (int i = 0; i < nprocs; i++) {
          proc p = proctab[i];
          if ((uchar *) p->p_addr >= m->m_addr
              && (uchar *) p->p_addr < m->m_addr + m->m_length)
               jit_compile(p->p_addr);
     }
}
#endif

/* xmain_exit -- exit after program has finished */
void NORETURN xmain_exit(int status) {
#ifdef OBXDEB
     debug_break(NULL, NULL, NULL, "exit");
#endif
#ifdef PROFILE
     print_profile();
     if (lflag) dump_lcounts();
#endif
     exit(status);
}

/* error_exit -- exit after fatal error */
void NORETURN error_exit(int status) {
#ifdef OBXDEB
     debug_message("quit");
#endif
     exit(status);
}

int main(int ac, char *av[]) {
     argc = ac; argv = av;
     progname = argv[0];

     gc_init();
     interpreter = wrap_prim(interp);
     dyntrap = wrap_prim(dltrap);

#ifdef M64X32
     /* Allocate ob_res and statlink in 32-bit addressible storage */
     _result = (value *) scratch_alloc(2 * sizeof(value));
     _stat = (value **) scratch_alloc(sizeof(value *));
#endif

     load_image();
     run(entry);
     xmain_exit(0);
}

#ifdef JIT
void interp(value *bp) {
     panic("dummy interp called");
}
#endif

word wrap_prim(primitive *prim) {
#ifdef JIT
     return vm_wrap((funptr) prim);
#else
#ifndef M64X32
     return (word) prim;
#else
     primitive **wrapper =
          (primitive **) scratch_alloc(sizeof(primitive *));
     *wrapper = prim;
     return address(wrapper);
#endif
#endif
}