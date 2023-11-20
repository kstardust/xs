#include <gic.h>
#include <common.h>
#include <platform.h>
#include <string.h>

static volatile gic_distributor_registers  *gic_dis;
static volatile gic_cpu_interface_registers *gic_cinf;

static gic_handler handlers[MAX_GIC_ID];

void
gic_init()
{
    gic_clear_all_pending();
    
    gic_dis = (volatile gic_distributor_registers*)GIC_DISTR_BASE;
    gic_cinf = (volatile gic_cpu_interface_registers*)GIC_CPUINTER_BASE;
    
    gic_cinf->CCPMR = 0xff;
    gic_cinf->CCTLR = 0x3;
    gic_cinf->CBPR  = 0;
    gic_dis->DCTLR = 0x3;    
    printf("CTLF %d\n", gic_dis->DCTLR);
    MEMORY_BARRIER;
}

void
gic_enable_interrupt(uint32_t id)
{
    uint8_t offset = (id >> 5);
    uint8_t bit = id & ((1 << 5) - 1);
    gic_dis->DISENABLER[offset] |= (1 << bit);
 
    // TODO: target PE for SPI
    MEMORY_BARRIER;
}

uint32_t
gic_interrupt_acknowledge()
{
    return gic_cinf->CIAR;    
}

void
gic_end_interrupt(uint32_t id)
{
    gic_cinf->CAEOIR = id;
    MEMORY_BARRIER;
}

void
gic_register_handler(uint32_t id, gic_handler handler)
{
    handlers[id] = handler;
}

uint32_t
gic_get_pending(uint32_t id)
{
    uint8_t offset = (id >> 5);
    uint8_t bit = id & ((1 << 5) - 1);    
    return (gic_dis->DISPENDR[offset] & (1 << bit)) != 0;
}


void
gic_clear_all_pending()
{
    for (uint32_t id = gic_interrupt_acknowledge();
         id != GIC_SPURIOUS_INTID ; id = gic_interrupt_acknowledge()) {
        gic_end_interrupt(id);
    }
}
