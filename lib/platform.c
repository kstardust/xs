#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <uart_io.h>

extern unsigned char __heap_start[];
extern unsigned char __heap_end[];

static unsigned char *heap_break = __heap_start;

static int
console_putc(char c, FILE *file)
{
    (void)file;
    uart_write(c);
    return (unsigned char)c;
}

static int
console_getc(FILE *file)
{
    unsigned char c;

    (void)file;
    uart_read(&c);
    return c;
}

static FILE console = FDEV_SETUP_STREAM(console_putc, console_getc, NULL,
    _FDEV_SETUP_RW);

FILE *const stdin = &console;
FILE *const stdout = &console;
FILE *const stderr = &console;

void *
sbrk(ptrdiff_t increment)
{
    unsigned char *previous = heap_break;

    if (increment < 0 || (size_t)(__heap_end - heap_break) < (size_t)increment) {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_break += increment;
    return previous;
}

int
gettimeofday(struct timeval *time_value, void *timezone)
{
    uint64_t counter;
    uint64_t frequency;

    (void)timezone;
    if (time_value == NULL) {
        errno = EFAULT;
        return -1;
    }

    __asm__ volatile("mrs %0, cntvct_el0" : "=r"(counter));
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(frequency));
    time_value->tv_sec = (time_t)(counter / frequency);
    time_value->tv_usec = (suseconds_t)(((counter % frequency) * 1000000U) /
        frequency);
    return 0;
}

_Noreturn void
_exit(int status)
{
    (void)status;
    for (;;)
        __asm__ volatile("wfe");
}

_Noreturn void
abort(void)
{
    _exit(1);
}
