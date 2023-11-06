#ifndef _C_COMMON
#define _C_COMMON

#include <ctypes.h>

void* memset(void *s, int c, size_t n);
void* memcpy(void *dest, const void *src, size_t n);
void* malloc(size_t size);
void putchar(int c);

#define READ32(x) (*(volatile uint32_t*)((x)))
#define READ64(x) (*(volatile uint64_t*)((x)))

#define WRITE32(x, y) (*(volatile uint32_t*)((x)) = (y))
#define WRITE64(x, y) (*(volatile uint64_t*)((x)) = (y))

#endif
