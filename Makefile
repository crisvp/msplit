# vim: noet

VERSION = 7372
INSTALL_DIR=/usr/local/

CC=gcc
CFLAGS=-I./include -DVERSION=$(VERSION) -Wall

TARGET = msplit
export

.PHONY: src include

all: include src

src:
	$(MAKE) -C src

include:
	$(MAKE) -C include

install: all
	install -m 0755 src/$(TARGET) $(INSTALL_DIR)/bin/$(TARGET)

clean:
	rm -f src/*.o src/$(TARGET)
