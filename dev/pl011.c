#include "pl011.h"

volatile uint32_t*
pl011_reg(uint64_t field)
{
    return (volatile uint32_t*)(field);
}

void
init_uart()
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

    // enable TX
    *tcr |= UARTTXE;
    
    // enable
    *tcr |= UARTEN;
}

void
wait_transmitting()
{
    while (*(pl011_reg(PL011_UARTFR)) & FR_BUSY) ;
}

void
uart_write(char c)
{
    wait_transmitting();
    *pl011_reg(PL011_UARTDR) = c & DATA_MASK;
    wait_transmitting();    
}
