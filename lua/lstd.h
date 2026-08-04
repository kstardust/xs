/*-
 * Minimal adaptation of FreeBSD stand/liblua/lstd.h for this kernel.
 * Filesystem-backed stdio is intentionally not exposed.
 */
#ifndef LSTD_H
#define LSTD_H

#include <stdio.h>
#include <string.h>
#include <io.h>

#define lua_writestringerror(s, p) do { printf((s), (p)); } while (0)

void luai_writestring(const char *, int);
#define lua_writestring(s, l) luai_writestring((s), (l))
#define lua_writeline() putchar('\n')

#endif
