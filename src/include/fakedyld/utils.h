#ifndef FAKEDYLD_UTILS_H
#define FAKEDYLD_UTILS_H

#include <paleinfo.h>

void spin();
int set_console_fd(int fd);
void disable_log_buffer();
void get_pinfo(struct paleinfo* pinfo_p);

#ifndef RAW_RAMDISK
#define RAW_RAMDISK "/dev/rmd0"
#endif

#ifndef RAMDISK
#define RAMDISK "/dev/md0"
#endif

static inline int p1_log(const char* format, ...) {
    printf("fakedyld: ");
    va_list va;
    va_start(va, format);
    int ret = vprintf(format, va);
    va_end(va);
    printf("\n");
    return ret;
}
#define LOG(...) p1_log(__VA_ARGS__)
#define CHECK_ERROR(action, msg) do { \
 int check_error_ret = action; \
 if (check_error_ret) { \
  LOG(msg ": %d", errno); \
  spin(); \
 } \
} while (0)

#endif
