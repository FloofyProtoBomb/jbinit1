all: launchd

launchd: launchd.c entitlements.xml
	$(CC) $(CFLAGS) $(LDFLAGS) launchd.c -o launchd
	$(LDID) -Icom.apple.xpc.launchd -Sentitlements.xml launchd

.PHONY: all
