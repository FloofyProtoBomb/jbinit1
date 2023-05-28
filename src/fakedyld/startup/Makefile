OBJECTS += $(patsubst %.c, %.o, $(wildcard *.c)) start.S.o

all: $(OBJECTS)

%.o: %.c
	$(CC) -c -nostdlibinc -I.. $(CFLAGS) $<

start.S.o: start.S
	$(CC) -c -nostdlibinc -I.. $(CFLAGS) start.S -o start.S.o

.PHONY: all
