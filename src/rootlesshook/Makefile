TARGET := iphone:clang:16.2:15.0
INSTALL_TARGET_PROCESSES = cfprefsd
FINALPACKAGE = 1
THEOS_PACKAGE_SCHEME = rootless
ARCHS = arm64

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = rootlesshooks

rootlesshooks_FILES = cfprefsd.x
rootlesshooks_CFLAGS = -fobjc-arc
rootlesshooks_LDFLAGS = -rpath /cores/binpack/Library/Frameworks

include $(THEOS_MAKE_PATH)/tweak.mk
