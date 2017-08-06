# vim: noet:

prefix = /usr/local

bin_path = $(prefix)/bin
man_path = $(prefix)/share/man
man1_man_path = $(man_path)/man1

# just bump this to some arbitrary number that's > current number
VERSION = 7378

CC=gcc
CFLAGS=-I./include -DVERSION=$(VERSION) -Wall

TARGET = msplit
export

all: include src

src:
	$(MAKE) -C src

include:
	$(MAKE) -C include

test:
	$(MAKE) -C test

install: all
	install -m 0755 -d $(DESTDIR)$(bin_path)
	install -m 0755 src/$(TARGET) $(DESTDIR)$(bin_path)/$(TARGET)
	install -m 0755 -d $(DESTDIR)$(man1_man_path)
	install -m 0644 man/msplit.1 $(DESTDIR)$(man1_man_path)/msplit.1

uninstall:
	rm -f $(DESTDIR)$(man1_man_path)/msplit.1
	rm -f $(DESTDIR)$(bin_path)/msplit
	-rmdir $(bin_path)
	-rmdir $(man1_man_path)

clean:
	-rm -f src/*.o src/$(TARGET) test/test test/*.o

.PHONY: src include test
