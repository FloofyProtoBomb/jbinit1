SHELL := /usr/bin/env bash
SRC = $(shell pwd)/src
CC = xcrun -sdk iphoneos clang
STRIP = strip
INSTALL = install
I_N_T = install_name_tool
CFLAGS += -I$(SRC)/include
ifeq ($(ASAN),1)
CFLAGS += -DASAN
endif
ifeq ($(DEV_BUILD),1)
CFLAGS += -DDEV_BUILD
DEV_TARGETS += xpchook.dylib
endif

ifeq ($(ASAN),1)
RAMDISK_SIZE = 8M
else ifeq ($(DEV_BUILD),1)
RAMDISK_SIZE = 1M
else
RAMDISK_SIZE = 512K
endif

LDID = ldid

export SRC CC CFLAGS LDFLAGS STRIP I_N_T LDID

all: ramdisk.dmg

bins:
	$(MAKE) -C src

ramdisk.dmg: bins
	sudo rm -rf ramdisk ramdisk.dmg
	mkdir -p ramdisk/{sbin,usr/lib,dev,mnt1,mnt2}
	$(INSTALL) -m755 src/fakedyld/fakedyld ramdisk/usr/lib/dyld
	$(INSTALL) -m755 src/launchd/launchd ramdisk/sbin/launchd
	sudo find ramdisk -exec chown 0:0 {} +
	hdiutil create -size $(RAMDISK_SIZE) -format UDRW -layout NONE -fs HFS+ -volname palera1nrd -srcfolder ./ramdisk ./ramdisk.dmg

clean:
	$(MAKE) -C src/fakedyld clean
	rm -f ramdisk.dmg
	sudo rm -rf ramdisk

.PHONY: all ramdisk.dmg bins
