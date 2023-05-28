CFLAGS += -miphoneos-version-min=15.0 -flto=thin -Oz -std=gnu17
CFLAGS += -Wall -Wextra -Wno-unused-parameter
CFLAGS += -Wno-unused-command-line-argument
export CFLAGS LDFLAGS

SUBDIRS = launchd fakedyld

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
