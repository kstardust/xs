#include <uart_io.h>


void
do_handle_empty()
{
    uart_print("empty\n");
}

void
do_handle_error()
{
    uart_print("ERROR\n");
}

void
do_handle_sync()
{
    uart_print("SYNC\n");   
}

void
do_handle_irq()
{
    uart_print("IRQ\n");
}
