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

long
strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p++;
    return p - s;
}
