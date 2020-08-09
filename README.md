# xml2pmx
Porting the XML2PMX music conversion tool to OBC.

Directory obsrc contains Oberon source code for the XML2PMX program

     b.m
     Complete.m
     Fifo.m
     MyFiles.m -- shim between Wirth-style and Spivey-style Files module
     Strings0.m
     Testbed.m

This root directory contains C source for a wrapper, invoked as xml2pmx.
Edit the main program here to implement --help, etc.

    wrapper.c

Here also is the bytecode for the program, written as a small collection
of array constants.

    image.c

This file contains machine-independent bytecode, and doesn't need to
be rebuilt when installing the program on a new machine.  To rebuild
it when installing a new version of the Oberon source, change to the
'obsrc' directory and say 'make'.

Also provided here is the C source for the bytecode interpreter

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

The bytecode interpreter is from release 3.1.0 of OBC, and rebuilding
of the bytecode file, if necessary, must be done with the same release
-- bytecode is not portable between releases because the opcodes
change.  Alternatively, update the source files here from a later
release.  Support for preloading of the kind used here is planned for
release 3.2 of OBC.
