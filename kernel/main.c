#include "pl011.h"

int
is_mmu_enabled()
{
  long sctlr;
  asm("mrs %0, sctlr_el1" : "=r" (sctlr));
  return sctlr & 1;
}

char msg[] = "hello world\n";

int
c_start()
{
    init_uart();
    char *i = msg;
    while (*i) {
        uart_write(*i++);
    }
    return 0;
}
