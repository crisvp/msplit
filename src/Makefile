# vim: noet

override CFLAGS	+= -I../include

OBJ     = delimiter.o matchsplit.o main.o

all: $(OBJ) $(TARGET)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
