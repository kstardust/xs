#ifndef _UART_IO
#define _UART_IO

void uart_print(const char *str);
void uart_write(char c);
void uart_init();
int uart_poll();
void uart_read(unsigned char *c);

#endif
