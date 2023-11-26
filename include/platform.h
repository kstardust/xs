#include <aa64reg.h>
#include <common.h>

#ifndef __PLATFORM
#define __PLATFORM

#define INST_SYNC_BARRIER asm volatile ("isb")
#define DATA_MEMORY_BARRIER asm volatile ("dmb sy")
#define MEMORY_BARRIER asm volatile ("dsb sy")

static inline void
enable_intr()
{
    asm volatile("msr daifclr, #(" XSTRING(DAIF_I) ")");
}

static inline void
disable_intr()
{
    asm volatile("msr daifset, #(" XSTRING(DAIF_I) ")");
}

static inline void
wfe()
{
    asm volatile("wfe");
}


#endif
