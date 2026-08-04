/* FreeBSD's gdtoa import adapted to Lua's numeric conversion hooks. */
#include "gdtoaimp.h"

char *__g_dfmt(char *, double *, int, size_t);

int
lua_number2str_impl(char *buffer, size_t size, double value)
{
    char *end = g_dfmt(buffer, &value, 14, size);

    if (end == NULL) {
        if (size != 0)
            buffer[0] = '\0';
        return 0;
    }
    return (int)(end - buffer);
}

double
lua_str2number_impl(const char *text, char **end)
{
    extern double strtod(const char *, char **);
    return strtod(text, end);
}
