# configure.ac for XML2PMX

AC_INIT(xml2pmx, 2020-06-04, rdt@cs.queensu.ca)
AC_CONFIG_SRCDIR(runtime/obx.h)
AC_CONFIG_AUX_DIR(scripts)
AC_CONFIG_FILES(Makefile runtime/Makefile)
AC_CONFIG_HEADERS(platform.h)

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

FIXUP=cat

case $host in
  *-*-linux-*)
    AC_DEFINE(HAVE_MMAP, 1, [Define if mmap available]);;
  *-*-mingw*|*-*-cygwin)
    AC_DEFINE(WINDOWS, 1, [Define to enable hacks for Windows])
    AC_SUBST(EXEEXT, ".exe")
    FIXUP=d2u;;
  *-*-darwin*)
    AC_DEFINE(MACOS, 1, [Define to enable hacks for MacOS X])
    AC_DEFINE(HAVE_MMAP, 1)
    AC_SUBST(PLATFLAGS, "-pagezero_size 0x1000");;
  *-*-freebsd*)
    AC_DEFINE(FREEBSD, 1, [Define to enable hacks for FreeBSD])
    AC_DEFINE(HAVE_MMAP, 1);;
esac

AC_SUBST(FIXUP)

case $host in
  i686-*)
    AC_DEFINE(UNALIGNED_MEM, 1, [Define if unaligned loads and stores work]);;
  x86_64-*)
    AC_DEFINE(M64X32, 1, [Define for 64-bit runtime with 32-bit pointers])
    AC_DEFINE(UNALIGNED_MEM, 1, [Define if unaligned loads and stores work]);;
esac

AC_OUTPUT
