#include <gic.h>
#include <common.h>
#include <platform.h>

static volatile gic_distributor_registers  *gic_dis;
static volatile gic_cpu_interface_registers *gic_cinf;

void
gic_init()
{
    gic_dis = (volatile gic_distributor_registers*)GIC_DISTR_BASE;
    gic_cinf = (volatile gic_cpu_interface_registers*)GIC_CPUINTER_BASE;
    
    gic_cinf->CCPMR = 0xffff;
    gic_cinf->CCTLR = 0x1;
    gic_dis->DCTLR = 0x3;

    MEMORY_BARRIER;
}

void
gic_enable_interrupt(uint32_t id)
{
    MEMORY_BARRIER;
}

uint32_t
gic_interrupt_acknowledge()
{
    return gic_cinf->CIAR;
}
