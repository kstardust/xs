#ifndef __PLATFORM
#define __PLATFORM

#define INST_SYNC_BARRIER asm volatile ("isb");
#define DATA_MEMORY_BARRIER asm volatile ("dmb sy");
#define MEMORY_BARRIER asm volatile ("dsb sy");

#endif
