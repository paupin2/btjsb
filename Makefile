SOURCE:=btjsb.c
BINARY:=btjsb
DESTINATION:=/usr/bin/btjsb

.PHONY: example

build: $(BINARY)

install: $(BINARY)
	cp $(BINARY) $(DESTINATION)

$(BINARY): $(SOURCE)
	gcc --std=c99 -Werror -O3 -o $@ $(SOURCE)
	@echo "$@ build; do \"make install\" to install to $(DESTINATION)"

clean:
	rm -f $(BINARY)
	make -C example clean

example:
	make -C example
