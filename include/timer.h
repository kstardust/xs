#ifndef  _TIMER_H
#define  _TIMER_H

#include <ctypes.h>

#define TIMER_INTID 0xe + 0x10 // from devicetree, PPI starts from 0x10
#define HZ 100

void timer_init();

void set_timer(uint32_t freq);

#endif
