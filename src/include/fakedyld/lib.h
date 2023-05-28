#ifndef FAKEDYLD_LIB_H
#define FAKEDYLD_LIB_H
#include <fakedyld/types.h>
#include <stddef.h>

void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

#endif
