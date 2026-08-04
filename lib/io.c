#include <io.h>
#include <stddef.h>
#include <time.h>
#include <uart_io.h>

void
putchar(int c)
{
    uart_write((char)c);
}

time_t
time(time_t *result)
{
    unsigned long counter;
    unsigned long frequency;
    time_t seconds;

    __asm__ volatile("mrs %0, cntvct_el0" : "=r"(counter));
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(frequency));
    seconds = (time_t)(counter / frequency);
    if (result != NULL)
        *result = seconds;
    return seconds;
}
