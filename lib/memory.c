#include <common.h>
#include <ctypes.h>

static size_t allocated = 0;

/* 
 * Calls to memset/memcpy may be emitted implicitly by GCC or MSVC
 * even when -ffreestanding or /NODEFAULTLIB are in effect.
 */
void*
memset(void *s, int c, size_t n)
{
    unsigned char *p = s;

    while (n--)
        *p++ = c;

    return s;
}

void*
memcpy(void *dest, const void *src, size_t n)
{
    const unsigned char *q = src;
    unsigned char *p = dest;

    while (n--)
        *p++ = *q++;

    return dest;
}

void *
malloc(size_t size)
{
    // abort
    *(volatile int *)(0) = 1;

    return NULL;
}
