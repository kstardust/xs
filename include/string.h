#ifndef __STRING_H__
#define __STRING_H__

#include <ctypes.h>

extern char hex2ascii_data[];

size_t strlen(const char *s);
#define	hex2ascii(hex)	(hex2ascii_data[hex])
#define isascii(c)	(((c) & ~0x7F) == 0)

int isupper(int c);
int islower(int c);
int toupper(int c);
int tolower(int c);
int memcmp(const void *a, const void *b, size_t n);
void *memchr(const void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int value, size_t n);
void *memmove(void *dest, const void *src, size_t n);
char *strchr(const char *s, int c);
char *strpbrk(const char *s, const char *accept);
char *strcpy(char *dest, const char *src);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strstr(const char *haystack, const char *needle);
int strcoll(const char *a, const char *b);
size_t strspn(const char *s, const char *accept);

int printf(const char *fmt, ...);
int sprintf(char *buf, const char *cfmt, ...);
int snprintf(char *buf, size_t size, const char *cfmt, ...);

#endif
