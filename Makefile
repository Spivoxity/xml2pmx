# Makefile

all: xml2pmx

# Concatenate the Oberon runtime 'obx' and the byteccode 'xml2pmx.x' to
# form an executable.  The runtime looks for bytecode at the end of its
# own executable: this works on Windows too.
xml2pmx: runtime/obx src/xml2pmx.x
	cat $^ >$@
	chmod +x $@

runtime/obx: force
	$(MAKE) -C $(@D) $(@F)

TEST := $(patsubst %,test-%,$(notdir $(wildcard test/*.xml)))

test: $(TEST)

test-%.xml: force
	./xml2pmx test/$*.xml $*.pmx a 0
	cmp test/$*.exp $*.pmx && echo "**PASSED**"
	@rm -r $*.pmxprep $*.pmx

clean realclean: %: %here
	$(MAKE) -C runtime $@

cleanhere: force
	rm -f xml2pmx Telemann.*

realcleanhere: cleanhere
	rm -f configure config.status config.log platform.h

force:
