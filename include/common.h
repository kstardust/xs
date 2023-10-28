#ifndef _C_COMMON
#define _C_COMMON

#include <ctypes.h>

void* memset(void *s, int c, size_t n);
void* memcpy(void *dest, const void *src, size_t n);
void* malloc(size_t size);
void putchar(int c);

#endif
