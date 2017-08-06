# vim: noet

override CFLAGS	+= -I../include

OBJ     = test.o ../src/matchsplit.o

all: $(OBJ) test

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
