SHELL=/bin/bash

all: precompile
	export PLBXML_FILELIST="$(shell cat src.txt)"; \
	$(MAKE) -f Makefile.plb debug=false profile=false optimize=true; \
	rm src.txt;

debug: precompile
	export PLBXML_FILELIST="$(shell cat src.txt)"; \
	$(MAKE) -f Makefile.plb debug=true optimize=false; \
	rm src.txt;

profile: precompile
	export PLBXML_FILELIST="$(shell cat src.txt)"; \
	$(MAKE) -f Makefile.plb debug=false optimize=false profile=true; \
	rm src.txt;

precompile:
	./precompile.sh

clean:
	rm -f *.o plbXml ;
	./precompile.sh clean;
	$(MAKE) -f Makefile.plb clean;
