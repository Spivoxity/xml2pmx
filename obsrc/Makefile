# src/Makefile

TARGET = ../image.c
OBJS = MyFiles.k Strings1.k Fifo.k b.k Complete.k Testbed.k

all: $(TARGET)

$(TARGET): xml2pmx.x preload
	./preload $< >$@

xml2pmx.x: $(OBJS)
	obc $^ -o $@ 

preload: preload.o
	gcc $(CFLAGS) $^ -o $@

CC = gcc
CFLAGS = -I ..

TEST := $(patsubst %,test-%,$(notdir $(wildcard ../test/*.xml)))

test: $(TEST)

test-%.xml: force
	./xml2pmx.x ../test/$*.xml $*.pmx a 0
	cmp ../test/$*.exp $*.pmx && echo "**PASSED**"

%.k: %.m
	obc -c -x $< -o $@

clean: force
	rm -f *.k *.o preload
	rm -f xml2pmx.x

realclean: clean

spotless: realclean

force:

###

b.k: Strings1.k Fifo.k MyFiles.k
Complete.k: Strings1.k MyFiles.k
Testbed.k: Strings1.k b.k Complete.k MyFiles.k
