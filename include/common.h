#ifndef _C_COMMON
#define _C_COMMON

#include <stddef.h>
#include <stdint.h>

#define READ32(x) (*(volatile uint32_t*)((x)))
#define READ64(x) (*(volatile uint64_t*)((x)))

#define WRITE32(x, y) (*(volatile uint32_t*)((x)) = (y))
#define WRITE64(x, y) (*(volatile uint64_t*)((x)) = (y))

#define STRING(x) #x
#define XSTRING(x) STRING(x)

#endif
