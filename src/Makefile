all: xml2pmx

# BYTECODE

update: xml2pmx.x 

OBJS = MyFiles.k Strings0.k Fifo.k b.k Complete.k Testbed.k

xml2pmx.x: $(OBJS)
	obc $^ -o $@ 

%.k: %.m
	obc -c $< -o $@


# RUNTIME

OBX = gc.o interp.o loader.o support.o xmain.o dynlink.o \
	Args.o Builtin.o Files.o primtab.o wrapper.o

interp.o: action.c

xmain.o: CFLAGS += -DREVID=\"xml2pmx\" -Dmain=xmain

xml2pmx: $(OBX)
	gcc $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

CFLAGS = -O2 -fno-strict-aliasing

# IMPORT

import pristine: force
	make -f Makefile.import $@


rtest: Strings0.k RTest.k
	obc $^ -o $@

test: force
	./xml2pmx Telemann.xml Telemann.pmx a 0
	cmp Telemann.exp Telemann.pmx && echo "**PASSED**"

clean: force
	rm -f *.o *.k xml2pmx Telemann.pmx *.pmxprep

force:

###

b.k: Strings0.k Fifo.k MyFiles.k
Complete.k: Strings0.k MyFiles.k
Testbed.k: Strings0.k b.k Complete.k MyFiles.k

$(OBX): config.h exec.h keiko.h obcommon.h obx.h primtab.h
