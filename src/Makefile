OBJS = MyFiles.k Strings0.k Fifo.k b.k Complete.k Testbed.k

all: xml2pmx

xml2pmx: $(OBJS)
	obc $^ -o $@ 

%.k: %.m
	obc -c $< -o $@

clean: force
	rm *.k xml2pmx

force:

###

b.k: Strings0.k Fifo.k MyFiles.k
Complete.k: Strings0.k MyFiles.k
Testbed.k: Strings0.k b.k Complete.k MyFiles.k
