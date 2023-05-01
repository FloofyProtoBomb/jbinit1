LAUNCHCTL_OBJ = bootstrap.o xpc_helper.o load.o
OBJECTS  = main.o

SUBDIRS = loader p1ctl utils helper

CFLAGS  += -miphoneos-version-min=15.0 -arch arm64 -Os -I.
LDFLAGS += ${THEOS}/sdks/iPhoneOS14.5.sdk/System/Library/PrivateFrameworks/APFS.framework/APFS.tbd -framework IOKit -framework CoreFoundation -framework Foundation -lobjc

ifeq ($(ASAN),1)
CFLAGS += -fsanitize=address,undefined
endif

CFLAGS += -I$(shell pwd)/iphoneos_headers -I$(shell pwd)/local_include -DLOCAL_BUILD -Wno-availability

all: local_init jbloader

local_init:
	$(RM) -r iphoneos_headers
	mkdir iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/System/Library/Frameworks/IOKit.framework/Headers iphoneos_headers/IOKit
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/libkern iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/xpc iphoneos_headers
	ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/launch.h iphoneos_headers
	
	cd launchctl && $(RM) -r iphoneos_headers
	cd launchctl && mkdir iphoneos_headers
	cd launchctl && ln -s $(shell xcrun -sdk macosx -show-sdk-path)/System/Library/Frameworks/IOKit.framework/Headers iphoneos_headers/IOKit
	cd launchctl && ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/libkern iphoneos_headers
	cd launchctl && ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/xpc iphoneos_headers
	cd launchctl && ln -s $(shell xcrun -sdk macosx -show-sdk-path)/usr/include/launch.h iphoneos_headers
	cd launchctl && xcrun -sdk iphoneos cc -Iiphoneos_headers --target=arm64-apple-ios15.0 -c xpc_helper.c -Wl,-sectcreate,__TEXT,__info_plist,Info.plist
	cd launchctl && xcrun -sdk iphoneos cc -Iiphoneos_headers --target=arm64-apple-ios15.0 -c bootstrap.c -Wl,-sectcreate,__TEXT,__info_plist,Info.plist
	cd launchctl && xcrun -sdk iphoneos cc -Iiphoneos_headers --target=arm64-apple-ios15.0 -c load.c -Wl,-sectcreate,__TEXT,__info_plist,Info.plist
	cd launchctl && $(RM) -r iphoneos_headers

$(SUBDIRS):
	$(MAKE) -C $@ all

jbloader: $(OBJECTS) $(SUBDIRS) $(patsubst %.o, launchctl/%.o, $(LAUNCHCTL_OBJ))
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(patsubst %.o, launchctl/%.o, $(LAUNCHCTL_OBJ)) $(patsubst %.c, %.o, $(wildcard $(patsubst %, %/*.c, $(SUBDIRS)))) -o jbloader
	$(STRIP) jbloader
ifeq ($(ASAN),1)
	$(I_N_T) -add_rpath /cores jbloader
endif
	ldid -S$(SRC)/ent.xml -Icom.apple.jbloader jbloader

xpchook.dylib:
	$(MAKE) -C launchctl/tools LDFLAGS="$(LDFLAGS) $(CFLAGS)" xpchook.dylib
	ldid -S launchctl/tools/xpchook.dylib

%.o: %.c
	$(CC) -c $(CFLAGS) $<

$(patsubst %.o, launchctl/%.o, $(LAUNCHCTL_OBJ)): $(patsubst %.o, launchctl/%.c, $(LAUNCHCTL_OBJ)) 
	$(MAKE) -C launchctl $(shell echo $@ | cut -d/ -f2)

create_fakefs_sh.c: create_fakefs.sh
	xxd -iC create_fakefs.sh > create_fakefs_sh.c

.PHONY: all xpchook.dylib $(SUBDIRS)
