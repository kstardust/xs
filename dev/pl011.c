#include <platform.h>
#include <common.h>
#include "pl011.h"


volatile uint32_t*
pl011_reg(uint64_t field)
{
    return (volatile uint32_t*)(field);
}

void
wait_transmitting()
{
    while (*(pl011_reg(PL011_UARTFR)) & FR_BUSY)
        ;
}

void
uart_init()
{  
    volatile uint32_t *rate_i = pl011_reg(PL011_UARTIBRD);
    volatile uint32_t *rate_f = pl011_reg(PL011_UARTFBRD);
    volatile uint32_t *tcr = pl011_reg(PL011_UARTCR);
    volatile uint32_t *lcr = pl011_reg(PL011_UARTLCR_H);

    // disable uart
    *tcr &= ~UARTEN;
    
    // disable FIFO
    *lcr &= ~UARTFEN;
    
    // drain
    wait_transmitting();
    
    // faction part is 6bits, the smallest unit is 2^-6 = 1/64
    // div = 64 * (UARTCLK / BAUDRATE * 16)
    uint32_t div = (UARTCLK << 2) / BAUDRATE;
    *rate_f = div & 0x3f;       // 6-bit
    *rate_i = (div >> 6) & 0xffff;  // 16-bit

    *lcr = 0;
    
    // two stop bits, even parity
    *lcr |= (UARTSTP2 | UARTPEN | UARTEPS);
    
    // word length
    *lcr |= WLEN_8;

    // mask all interrupts
    *pl011_reg(PL011_UARTIMSC) = UARTINTMASK;
	  
    // disable DMA
    *pl011_reg(PL011_UARTDMACR) = 0;

    // enable TX/RX
    *tcr |= (UARTTXE | UARTRXE);
    
    // enable
    *tcr |= UARTEN;

    MEMORY_BARRIER;
}

void
uart_write(char c)
{
    wait_transmitting();
    WRITE32(PL011_UARTDR, c & DATA_MASK);
    wait_transmitting();    
}

int
uart_poll()
{
    return READ32(PL011_UARTFR) & FR_RXFE;
}

void
uart_read(unsigned char *c)
{
    while (uart_poll() != 0);
    *c = READ32(PL011_UARTDR) & DATA_MASK;
}

