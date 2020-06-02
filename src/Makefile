# src/Makefile

all:

# Only recompile the program (using installed obc) on 'make update'
update: xml2pmx.x 

OBJS = MyFiles.k Strings1.k Fifo.k b.k Complete.k Testbed.k

xml2pmx.x: $(OBJS)
	obc $^ -o $@ 

TEST := $(patsubst %,test-%,$(notdir $(wildcard ../test/*.xml)))

test: $(TEST)

test-%.xml: force
	./xml2pmx.x ../test/$*.xml $*.pmx a 0
	cmp ../test/$*.exp $*.pmx && echo "**PASSED**"

%.k: %.m
	obc -c -x $< -o $@

clean: force
	rm -f *.k

realclean: force

spotless: realclean
	rm -f xml2pmx.x

force:

###

b.k: Strings1.k Fifo.k MyFiles.k
Complete.k: Strings1.k MyFiles.k
Testbed.k: Strings1.k b.k Complete.k MyFiles.k
