#ifndef FIXHEADER_H
#define FIXHEADER_H

#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CFUserNotification.h>

// override API_AVAILABLE values
/*-- IOKit --*/
extern const mach_port_t kIOMasterPortDefault
__API_AVAILABLE(macCatalyst(1.0), ios(9.0))
__API_DEPRECATED_WITH_REPLACEMENT("kIOMainPortDefault", macos(10.0, 12.0)) __API_UNAVAILABLE(watchos, tvos);

/*-- CoreFoundation --*/
CF_EXPORT
CFUserNotificationRef CFUserNotificationCreate(CFAllocatorRef allocator, CFTimeInterval timeout, CFOptionFlags flags, SInt32 *error, CFDictionaryRef dictionary) API_AVAILABLE(macos(10.0), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

CF_EXPORT
const CFStringRef kCFUserNotificationAlertMessageKey API_AVAILABLE(macos(10.0), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

CF_EXPORT
const CFStringRef kCFUserNotificationAlertHeaderKey API_AVAILABLE(macos(10.0), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

#endif
