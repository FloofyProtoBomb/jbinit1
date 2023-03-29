OBJECTS  = create_fakefs_sh.o enable_ssh.o fakefs.o lock_vars.o
OBJECTS += get_boot_manifest_hash.o info.o bakera1nd.o launchd.o
OBJECTS += jbloader.o mount_dmg.o obliterator.o p1ctl.o main.o
OBJECTS += prep_launch.o remount.o runcmd.o safemode_alert.o
OBJECTS += sbreload.o spin.o uicache.o sysstatuscheck.o print_info.o
OBJECTS += get_set_flags.o launchctl/xpc_helper.o launchctl/bootstrap.o
OBJECTS += launchctl/load.o get_dyld_platform.o

CFLAGS  += -miphoneos-version-min=7.0 -arch arm64 -Os -I.
#LDFLAGS += $(SRC)/APFS.tbd -framework IOKit -framework CoreFoundation -framework Foundation -lobjc
LDFLAGS += ${THEOS}/sdks/iPhoneOS14.5.sdk/System/Library/PrivateFrameworks/APFS.framework/APFS.tbd -framework IOKit -framework CoreFoundation -framework Foundation -lobjc
ifeq ($(ASAN),1)
CFLAGS += -fsanitize=address,undefined
endif

CFLAGS += -Iiphoneos_headers -Ilocal_include -DLOCAL_BUILD -Wno-availability

all: local_init jbloader

local_init:
	$(RM) -r iphoneos_headers
	mkdir iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/System/Library/Frameworks/IOKit.framework/Headers iphoneos_headers/IOKit
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/libkern iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/xpc iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/launch.h iphoneos_headers

%.o: %.c
	$(CC) -c $(CFLAGS) $<

launchctl/%.o: launchctl/%.c
	$(MAKE) -C launchctl $(shell echo $@ | cut -d/ -f2)

create_fakefs_sh.c: create_fakefs.sh
	xxd -iC create_fakefs.sh > create_fakefs_sh.c

jbloader: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o jbloader
	$(STRIP) jbloader
ifeq ($(ASAN),1)
	$(I_N_T) -add_rpath /cores jbloader
endif
	ldid -S$(SRC)/ent.xml -Icom.apple.jbloader jbloader

.PHONY: all
