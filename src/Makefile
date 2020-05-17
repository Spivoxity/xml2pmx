OBJS = MyFiles.k Strings0.k Fifo.k b.k Complete.k Testbed.k

all: xml2pmx

xml2pmx: $(OBJS)
	obc $^ -o $@ 

%.k: %.m
	obc -c $< -o $@

test: force
	./xml2pmx Telemann.xml Telemann.pmx a 0
	cmp Telemann.exp Telemann.pmx

clean: force
	rm -f *.k xml2pmx Telemann.pmx *.pmxprep

force:

###

b.k: Strings0.k Fifo.k MyFiles.k
Complete.k: Strings0.k MyFiles.k
Testbed.k: Strings0.k b.k Complete.k MyFiles.k
