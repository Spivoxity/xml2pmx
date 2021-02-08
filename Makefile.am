bin_PROGRAMS = xml2pmx

xml2pmx_SOURCES = Args.c Builtin.c dynlink.c Files.c gc.c \
	image.c interp.c primtab0.c support.c xmain.c loader.c wrapper.c \
	exec.h keiko.h obcommon.h obx.h

# Add action.c (included in interp.c), the test subdirectory, and
# Oberon sources from the obsrc directory.
EXTRA_DIST = action.c test \
	obsrc/b.m obsrc/Complete.m obsrc/Fifo.m obsrc/Makefile \
	obsrc/MyFiles.m obsrc/preload.c obsrc/Strings1.m obsrc/Testbed.m

MYTESTS = p77 ActorPreludeSample BeetAnGeSample embracable \
	k545_korr25_orig MahlFaGe4Sample SchbAvMaSample Telemann

# echo -n doesn't work in MacOS as a shell builtin.
ECHO = /bin/echo

check:
	for f in $(MYTESTS); do \
	    $(ECHO) -n "$$f: "; \
	    if ./xml2pmx test/$$f.xml $$f.pmx a 0 >/dev/null \
		    && cmp test/$$f.exp $$f.pmx; then \
		$(ECHO) "PASS"; else $(ECHO) "FAIL"; fi; \
	done
