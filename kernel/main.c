#include <uart_io.h>
#include <string.h>
#include <virtio.h>
#include <timer.h>
#include <gic.h>
#include <platform.h>


int
is_mmu_enabled()
{
  long sctlr;
  asm("mrs %0, sctlr_el1" : "=r" (sctlr));
  return sctlr & 1;
}

void
get_timevalue()
{
  long sctlr;
  asm volatile("mrs %0, cntp_tval_el0" : "=r" (sctlr));
  if (sctlr <= 10000)
      printf("timervalue %d\n", sctlr);
}

int
c_start()
{ 
    gic_init();
    timer_init();
    uart_init();
    virtio_init();

    printf("hello\n");
 
    while (1) {
        wfe();
    }

    return 0;
}

void
uart_test()
{
    unsigned char c;
    while (1) {
        uart_read(&c);
        uart_write(c);
        if (c == '\r')
            uart_write('\n');
    }
}
