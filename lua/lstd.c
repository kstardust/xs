/*-
 * Derived from FreeBSD stand/liblua/lstd.c.
 * Copyright (c) 2014 Pedro Souza <pedrosouza@freebsd.org>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "lstd.h"

void
luai_writestring(const char *s, int length)
{
    while (length-- > 0)
        putchar(*s++);
}
