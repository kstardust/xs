#include <uart_io.h>
#include <string.h>

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
    uart_init();
    printf("%s\n", msg);    
    return 0;
}
