
hook_FRAMEWORKS += -framework Foundation -framework CoreFoundation CydiaSubstrate.framework/CydiaSubstrate.tbd
hook_LDFLAGS += -rpath /var/jb/Library/Frameworks
hook_LDFLAGS += -rpath /var/jb/usr/lib
hook_LDFLAGS += -rpath /cores/binpack/Library/Frameworks
hook_LDFLAGS += -rpath /cores/binpack/usr/lib

all: cfprefsd.dylib

cfprefsd.dylib: cfprefsd.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(hook_LDFLAGS) $(hook_FRAMEWORKS) cfprefsd.c -miphoneos-version-min=15.0 -arch arm64 -Os -Wall -Wextra -Wno-unused-parameter -shared -o rootlesshooks.dylib
	$(I_N_T) -id '/cores/binpack/usr/lib/rootlesshooks.dylib' rootlesshooks.dylib
	ldid -S rootlesshooks.dylib
