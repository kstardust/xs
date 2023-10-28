#include <uart_io.h>

void
uart_print(const char *str)
{
    while (*str)
        uart_write(*str++);
}
