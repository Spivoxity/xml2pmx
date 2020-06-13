# configure.ac for XML2PMX

AC_INIT(xml2pmx, 2020-06-04, rdt@cs.queensu.ca)
AC_CONFIG_AUX_DIR(scripts)
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR(runtime/obx.h)
AC_CONFIG_FILES(Makefile runtime/Makefile)
AC_CONFIG_HEADERS(config.h)
AC_DEFINE(REVID, "xml2pmx", [Build id for runtime])

AC_CANONICAL_HOST
AC_PROG_CC
AC_C_CONST
AC_C_BIGENDIAN
AC_C_INLINE
AC_C_INDEXED_JUMPS
AC_C_UNUSED
AC_C_USED
AC_C_NORETURN
AC_FIND_PAGESIZE
AC_CHECK_FUNCS(mmap)

FIXUP=cat

case $host in
  *-*-mingw*|*-*-cygwin)
    AC_DEFINE(WINDOWS, 1, [Define to enable hacks for Windows])
    FIXUP=d2u;;
  *-*-darwin*)
    AC_DEFINE(MACOS, 1, [Define to enable hacks for MacOS X])
    AC_SUBST(LDFLAGS, "-pagezero_size 0x1000");;
esac

case $host in
  i686-*)
    AC_DEFINE(UNALIGNED_MEM, 1, [Define if unaligned loads and stores work]);;
  x86_64-*)
    AC_DEFINE(M64X32, 1, [Define for 64-bit runtime with 32-bit pointers])
    AC_DEFINE(UNALIGNED_MEM, 1, [Define if unaligned loads and stores work]);;
esac

AC_SUBST(FIXUP)

AC_OUTPUT
