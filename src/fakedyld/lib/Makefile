OBJECTS += $(patsubst %.c, %.o, $(wildcard *.c)) msyscall.S.o

all: $(OBJECTS)

%.o: %.c
	$(CC) -c -nostdlibinc -I.. $(CFLAGS) $<

msyscall.S.o: msyscall.S
	$(CC) -c -nostdlibinc -I.. $(CFLAGS) msyscall.S -o msyscall.S.o

.PHONY: all
