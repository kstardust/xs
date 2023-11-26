#include <uart_io.h>
#include <aa64reg.h>
#include <gic.h>

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
    gic_isr();
}
