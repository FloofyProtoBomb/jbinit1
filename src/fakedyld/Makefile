SUBDIRS = lib main patch_dyld startup utils

CFLAGS += -ffreestanding -nostdlib -fno-stack-protector
LDFLAGS += -e__dyld_start -Wl,-dylinker -Wl,-dylinker_install_name,/usr/lib/dyld
LDFLAGS += -static -Wl,-fatal_warnings -Wl,-dead_strip -Wl,-Z

all: fakedyld

$(SUBDIRS):
	$(MAKE) -C $@

fakedyld: $(SUBDIRS)
	$(CC) $(CFLAGS) $(LDFLAGS) \
		$(patsubst %.c, %.o, $(wildcard $(patsubst %, %/*.c, $(SUBDIRS)))) \
		$(patsubst %.S, %.S.o, $(wildcard $(patsubst %, %/*.S, $(SUBDIRS)))) \
		-o fakedyld
	$(LDID) -Icom.apple.dyld -S fakedyld

clean:
	rm -f fakedyld
	find . -name '*.o' -delete

.PHONY: all $(SUBDIRS)
