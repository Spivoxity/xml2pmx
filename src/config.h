/* config.h -- Copyright (c) 2020 J. M. Spivey */

#include "platform.h"

/* Define if indexed jumps work. */
#define HAVE_INDEXED_JUMPS 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Log2 of page size */
#define LOG_PAGESIZE 12

/* Magic number for trailer */
#define MAGIC "OBCX"

/* Attribute for functions that don't return */
#define NORETURN __attribute__ ((noreturn))

/* Page size */
#define PAGESIZE 4096

/* Version signature for symbol tables */
#define SIG 0x00030100

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Attribute for unused variables */
#define UNUSED __attribute__ ((unused))

/* Attribute for used variables */
#define USED __attribute__ ((used))

