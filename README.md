# xml2pmx
Porting the XML2PMX music conversion tool to OBC.

Directory src contains Oberon source code for the XML2PMX program

     b.m
     Complete.m
     Fifo.m
     MyFiles.m
     Strings0.m
     Testbed.m

Also binary bytecode for the program

     xml2pmx.x

This bytecode is joined with the bytecode interpreter to make
an executable program: this avoids the problem of configuring one half
of the program to find the other at runtime.

Directory runtime contains C source for a wrapper, invoked as xml2pmx.
Edit the main program here to implement --help, etc.

    wrapper.c

Also C source for the bytecode interpreter

    action.c
    config.h
    dynlink.c -- doesn't actually do any dynamic linking
    exec.h
    gc.c
    interp.c
    keiko.h
    kickstart.c
    obcommon.h
    obx.h
    primtab0.c
    support.c
    xmain.c
    Args.c
    Builtin.c
    Files.c
    image.c

Also a C program not included when the excutable is built.

    preload.c
    Makefile.import
    
Say 'make -f Makefile.import update' to generate image.c from ../src/xml2pmx.x 

The bytecode interpreter is from release 3.1.0 of OBC, and rebuilding
of the bytecode file, if necessary, must be done with the same release
-- bytecode is not portable between releases because the opcodes
change.  Alternatively, update the source files here from a later
release.  Support for preloading of the kind used here is planned for
release 3.2 of OBC.
