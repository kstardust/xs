#include <timer.h>
#include <gic.h>
#include <platform.h>
#include <string.h>


static uint32_t freq;

void
timer_schedule()    
{
    uint64_t t = HZ * freq;
    asm volatile ("msr cntp_tval_el0, %0": : "r" (t));
}

void
timer_gic_handler()
{
    printf("tick\n");
    timer_schedule();
}

void
get_freq()
{
    /* cntfrq_el0 is only write-able at the highest implemented Exception level and readable at all Exception levels */
    asm volatile("mrs %0, cntfrq_el0" : "=r" (freq) :: "memory");
}

void
timer_init()
{
    get_freq();

    /* enable timer */
    asm volatile("msr cntp_ctl_el0, %x0\n\t":: "r" (1));
    
    timer_schedule();
    gic_register_handler(TIMER_INTID, timer_gic_handler);
    gic_enable_interrupt(TIMER_INTID);
}
