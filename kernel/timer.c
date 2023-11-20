#include <timer.h>
#include <gic.h>
#include <platform.h>
#include <string.h>


static uint32_t freq;

void
timer_gic_handler()
{
    printf("tick\n");
}

void
get_freq()
{
    // cntfrq_el0 is only write-able at the highest implemented Exception level and readable at all Exception levels
    asm volatile("mrs %0, cntfrq_el0" : "=r" (freq) :: "memory");
}

void
timer_init()
{
    get_freq();
    uint64_t t;
    t = 2 * freq;
    asm volatile (
         "mov x12, #1\n"
         "msr cntp_ctl_el0, x12\n"
         "isb\n"
         "mov x12, %0\n"
         "msr cntp_tval_el0, x12": : "r" (t) : "x12", "memory");
    gic_register_handler(TIMER_INTID, timer_gic_handler);
    gic_enable_interrupt(TIMER_INTID);
}
