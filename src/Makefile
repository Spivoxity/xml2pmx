# src/Makefile

all:

# Only recompile the program (using installed obc) on 'make update'
update: xml2pmx.x 

OBJS = MyFiles.k Strings0.k Fifo.k b.k Complete.k Testbed.k

xml2pmx.x: $(OBJS)
	obc $^ -o $@ 

%.k: %.m
	obc -c $< -o $@

clean: force
	rm -f *.k

realclean: force

spotless: realclean
	rm -f xml2pmx.x

force:

###

b.k: Strings0.k Fifo.k MyFiles.k
Complete.k: Strings0.k MyFiles.k
Testbed.k: Strings0.k b.k Complete.k MyFiles.k
