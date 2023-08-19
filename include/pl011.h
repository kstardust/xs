#ifndef _PL011_H
#define _PL011_H

#include "ctypes.h"

enum {
    PL011_UART_BASE = 0x9000000,               // from dts
    PL011_UARTDR = PL011_UART_BASE + 0x00,
    PL011_UARTRSR = PL011_UART_BASE + 0x04,
    PL011_UARTFR = PL011_UART_BASE + 0x018,
    PL011_UARTIBRD = PL011_UART_BASE + 0x024,
    PL011_UARTFBRD = PL011_UART_BASE + 0x028,
    PL011_UARTLCR_H = PL011_UART_BASE + 0x2c,    
    PL011_UARTCR = PL011_UART_BASE + 0x30,
    PL011_UARTIMSC = PL011_UART_BASE + 0x38,
    PL011_UARTDMACR = PL011_UART_BASE + 0x48
};

#define FR_BUSY (1 << 3)
#define UARTEN  1

#define UARTFEN   (1 << 4)
#define UARTSTP2  (1 << 3)
#define UARTEPS   (1 << 2)
#define UARTPEN   (1 << 1)

#define UARTTXE   (1 << 8)
#define UARTRXE   (1 << 9)

#define WLEN_8    0x60
#define DATA_MASK 0x7f
#define UARTINTMASK 0x7ff

#define UARTCLK 24000000 // from dts
#define BAUDRATE 115200  // default baudrate of qemu

void init_uart();
volatile uint32_t* pl011_reg(uint64_t field);
void wait_transmitting();
void uart_write(char c);

#endif
