SHELL=/bin/bash

all:
	./precompile.sh; \
	export PLBXML_FILELIST="$(shell cat src.txt)"; \
	$(MAKE) -f Makefile.plb

clean:
	rm *.o

