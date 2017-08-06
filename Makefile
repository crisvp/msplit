# vim: noet:

INSTALL_DIR=/usr/local/

# just bump this to some arbitrary number that's > current number
VERSION = 7372

CC=gcc
CFLAGS=-I./include -DVERSION=$(VERSION) -Wall

TARGET = msplit
export

.PHONY: src include test

all: include src

src:
	$(MAKE) -C src

include:
	$(MAKE) -C include

test:
	$(MAKE) -C test

install: all
	install -m 0755 src/$(TARGET) $(INSTALL_DIR)/bin/$(TARGET)
	install -m 0644 man/msplit.1 $(INSTALL_DIR)/share/man/man1/msplit.1

clean:
	rm -f src/*.o src/$(TARGET) test/test test/*.o
