#include <string.h>

char hex2ascii_data[] = "0123456789abcdefghijklmnopqrstuvwxyz";

int
isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

int 
islower(int c)
{
    return c >= 'a' && c <= 'z';
}

int
toupper(int c)
{
    return islower(c) ? c - 'a' + 'A' : c;
}

int
tolower(int c)
{
    return isupper(c) ? c - 'A' + 'a' : c;
}

size_t
strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p++;
    return p - s;
}

int strcmp(const char *a, const char *b) {
    while (*a != '\0' && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int strncmp(const char *a, const char *b, size_t n) {
    while (n != 0 && *a != '\0' && *a == *b) { a++; b++; n--; }
    return n == 0 ? 0 : (unsigned char)*a - (unsigned char)*b;
}

char *strstr(const char *haystack, const char *needle) {
    size_t length = strlen(needle);
    if (length == 0) return (char *)haystack;
    for (; *haystack != '\0'; haystack++)
        if (strncmp(haystack, needle, length) == 0) return (char *)haystack;
    return NULL;
}

int strcoll(const char *a, const char *b) { return strcmp(a, b); }

char *strcpy(char *dest, const char *src) {
    char *result = dest;
    while ((*dest++ = *src++) != '\0') ;
    return result;
}

char *strchr(const char *s, int c) {
    do { if (*s == (char)c) return (char *)s; } while (*s++ != '\0');
    return NULL;
}

char *strpbrk(const char *s, const char *accept) {
    for (; *s != '\0'; s++)
        if (strchr(accept, *s) != NULL) return (char *)s;
    return NULL;
}

size_t strspn(const char *s, const char *accept) {
    const char *start = s;
    while (*s != '\0' && strchr(accept, *s) != NULL) s++;
    return (size_t)(s - start);
}

int isdigit(int c) { return c >= '0' && c <= '9'; }
int isalpha(int c) { return isupper(c) || islower(c); }
int isalnum(int c) { return isalpha(c) || isdigit(c); }
int iscntrl(int c) { return (unsigned)c < 32 || c == 127; }
int isprint(int c) { return c >= 32 && c <= 126; }
int isgraph(int c) { return c >= 33 && c <= 126; }
int isspace(int c) { return c == ' ' || (c >= '\t' && c <= '\r'); }
int isxdigit(int c) { return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
int ispunct(int c) { return isgraph(c) && !isalnum(c); }
int abs(int value) { return value < 0 ? -value : value; }

long long
strtoll(const char *s, char **endp, int base)
{
    const char *start;
    unsigned long long value = 0;
    int negative = 0;
    int digit;

    while (isspace((unsigned char)*s))
        s++;
    if (*s == '-' || *s == '+')
        negative = (*s++ == '-');
    if ((base == 0 || base == 16) && s[0] == '0' &&
        (s[1] == 'x' || s[1] == 'X')) {
        base = 16;
        s += 2;
    } else if (base == 0) {
        base = (s[0] == '0') ? 8 : 10;
    }
    start = s;
    for (;;) {
        if (isdigit((unsigned char)*s))
            digit = *s - '0';
        else if (*s >= 'a' && *s <= 'z')
            digit = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'Z')
            digit = *s - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        value = value * (unsigned int)base + (unsigned int)digit;
        s++;
    }
    if (endp != NULL)
        *endp = (char *)(s == start ? start : s);
    return negative ? -(long long)value : (long long)value;
}
