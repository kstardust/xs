#include <uart_io.h>
#include <string.h>
#include <virtio.h>
#include <gic.h>


int
is_mmu_enabled()
{
  long sctlr;
  asm("mrs %0, sctlr_el1" : "=r" (sctlr));
  return sctlr & 1;
}

char msg[] = "hello world";

int
c_start()
{
    gic_init();    
    uart_init();
    virtio_init();

    printf("%s\n", msg);    
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
