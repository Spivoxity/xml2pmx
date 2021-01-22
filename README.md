# xml2pmx
Porting the XML2PMX music conversion tool to OBC.

Directory obsrc contains Oberon source code for the XML2PMX program

     b.m
     Complete.m
     Fifo.m
     MyFiles.m -- shim between Wirth-style and Spivey-style Files module
     Strings0.m -- Strings module ported from Wirth Oberon
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

Also provided here is the C source for the bytecode interpreter, some
of it machine-generated.

     action.c
     config.h
     dynlink.c
     exec.h
     gc.c
     interp.c
     keiko.h
     loader.c
     obcommon.h
     obx.h
     primtab0.c
     primtab.h
     support.c
     xmain.c
     Args.c
     Builtin.c
     Files.c

To avoid non-portable interfaces for storage allocation, this bytecode
interpreter implements its own segmented scheme for managing memory.
All storage allocation is done through malloc; the Oberon program uses
a 32-bit address space for data, and this is translated by the
bytecode interpreter into native pointers of 32 or 64 bits.

The bytecode interpreter is from release 3.2beta1 of OBC (should
become 3.2.0 without further change), and rebuilding of the bytecode
file, if necessary, must be done with the same release -- bytecode is
not portable between releases because the opcodes change.
Alternatively, update the source files here from a later release.

-- JMS, 22/1/21
