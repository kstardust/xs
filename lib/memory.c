#include <common.h>
#include <ctypes.h>

extern unsigned char _end[];

#define HEAP_SIZE (16UL * 1024UL * 1024UL)
#define ALIGNMENT 16UL

typedef struct block {
    size_t size;
    struct block *next;
    int free;
} block_t;

static block_t *heap_head;

static size_t align_size(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

static void heap_init(void) {
    uintptr_t start = ((uintptr_t)_end + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    heap_head = (block_t *)start;
    heap_head->size = HEAP_SIZE - sizeof(*heap_head);
    heap_head->next = NULL;
    heap_head->free = 1;
}

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

int memcmp(const void *a, const void *b, size_t n) {
    const unsigned char *p = a, *q = b;
    while (n--) {
        if (*p != *q) return (int)*p - (int)*q;
        p++; q++;
    }
    return 0;
}

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    while (n--) {
        if (*p == (unsigned char)c) return (void *)p;
        p++;
    }
    return NULL;
}

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    if (d < s) while (n--) *d++ = *s++;
    else if (d > s) {
        d += n; s += n;
        while (n--) *--d = *--s;
    }
    return dest;
}

void *
malloc(size_t size)
{
    block_t *block;
    size_t wanted;
    if (size == 0) return NULL;
    if (heap_head == NULL) heap_init();
    wanted = align_size(size);
    for (block = heap_head; block != NULL; block = block->next) {
        if (!block->free || block->size < wanted) continue;
        if (block->size >= wanted + sizeof(*block) + ALIGNMENT) {
            block_t *tail = (block_t *)((unsigned char *)(block + 1) + wanted);
            tail->size = block->size - wanted - sizeof(*block);
            tail->next = block->next;
            tail->free = 1;
            block->next = tail;
            block->size = wanted;
        }
        block->free = 0;
        return block + 1;
    }
    return NULL;
}

void free(void *ptr) {
    block_t *scan;
    if (ptr == NULL) return;
    ((block_t *)ptr - 1)->free = 1;
    for (scan = heap_head; scan != NULL && scan->next != NULL;) {
        if (scan->free && scan->next->free) {
            scan->size += sizeof(*scan) + scan->next->size;
            scan->next = scan->next->next;
        } else scan = scan->next;
    }
}

void *realloc(void *ptr, size_t size) {
    block_t *block;
    void *replacement;
    if (ptr == NULL) return malloc(size);
    if (size == 0) { free(ptr); return NULL; }
    block = (block_t *)ptr - 1;
    if (block->size >= size) return ptr;
    replacement = malloc(size);
    if (replacement == NULL) return NULL;
    memcpy(replacement, ptr, block->size);
    free(ptr);
    return replacement;
}

void abort(void) {
    for (;;) __asm__ volatile("wfe");
}
