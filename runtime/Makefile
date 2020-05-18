# runtime/Makefile

all: obx

OBX = gc.o interp.o loader.o support.o xmain.o dynlink.o \
	Args.o Builtin.o Files.o primtab.o wrapper.o

interp.o: action.c

xmain.o: CFLAGS += -DREVID=\"xml2pmx\" -Dmain=xmain

obx: $(OBX)
	gcc $(CFLAGS) -s $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

CFLAGS = -O2 -fno-strict-aliasing -I ..


import pristine: force
	make -f Makefile.import $@

clean: force
	rm -f *.o obx

realclean: clean

force:

###

$(OBX): config.h exec.h keiko.h obcommon.h obx.h primtab.h ../platform.h
