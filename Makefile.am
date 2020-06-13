SUBDIRS = runtime

MYTESTS = ActorPreludeSample BeetAnGeSample embracable \
	k545_korr25_orig MahlFaGe4Sample SchbAvMaSample Telemann

check:
	for f in $(MYTESTS); do \
	    echo -n "$$f: "; \
	    if runtime/xml2pmx test/$$f.xml $$f.pmx a 0 >/dev/null \
		    && ($(FIXUP) <$$f.pmx | cmp test/$$f.exp -); then \
		echo "PASS"; else echo "FAIL"; fi; \
	    rm -f $$f.pmxprep $$f.pmx; \
	done
