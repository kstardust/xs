#ifndef __STRING_H__
#define __STRING_H__

#include <ctypes.h>

extern char hex2ascii_data[];

long strlen(const char *s);
#define	hex2ascii(hex)	(hex2ascii_data[hex])
#define isascii(c)	(((c) & ~0x7F) == 0)

int isupper(int c);
int islower(int c);
int toupper(int c);
int tolower(int c);
long strlen(const char *s);

int printf(const char *fmt, ...);
int sprintf(char *buf, const char *cfmt, ...);
int snprintf(char *buf, size_t size, const char *cfmt, ...);

#endif
