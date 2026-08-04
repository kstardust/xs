#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

void abort(void) __attribute__((noreturn));
int abs(int value);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
double strtod(const char *s, char **endp);
long long strtoll(const char *s, char **endp, int base);
#endif
