#include <io.h>
#include <uart_io.h>

void
putchar(int c)
{
    uart_write((char)c);
}
