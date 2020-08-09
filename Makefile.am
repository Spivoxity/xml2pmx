bin_PROGRAMS = xml2pmx
xml2pmx_SOURCES = Args.c Builtin.c dynlink.c Files.c gc.c \
	image.c interp.c kickstart.c primtab0.c support.c wrapper.c xmain.c

MYTESTS = p77 ActorPreludeSample BeetAnGeSample embracable \
	k545_korr25_orig MahlFaGe4Sample SchbAvMaSample Telemann

ECHO = /bin/echo

check:
	for f in $(MYTESTS); do \
	    $(ECHO) -n "$$f: "; \
	    if ./xml2pmx test/$$f.xml $$f.pmx a 0 >/dev/null \
		    && ($(FIXUP) <$$f.pmx | cmp test/$$f.exp -); then \
		$(ECHO) "PASS"; else $(ECHO) "FAIL"; fi; \
	    rm -f $$f.pmx; \
	done
