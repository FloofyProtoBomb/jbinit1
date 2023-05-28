#ifndef FAKEDYLD_ERRNO_H
#define FAKEDYLD_ERRNO_H

#include <stdint.h>
#include <stddef.h>
#include <fakedyld/types.h>

int* __error();
#define errno (*__error())

#endif
