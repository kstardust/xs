#ifndef  _GIC_H
#define  _GIC_H

#include <ctypes.h>

typedef void (*gic_handler)();
    
#define MAX_GIC_ID 1024

#define GIC_SPURIOUS_INTID  1023 // see doc, this is for no pending interrupts
/*
  The format for interrupts in device tree:
  https://elixir.bootlin.com/linux/latest/source/Documentation/devicetree/bindings/interrupt-controller/arm,gic.yaml
*/

/* the address is derived from device tree
   the format: https://www.kernel.org/doc/Documentation/devicetree/bindings/interrupt-controller/arm%2Cgic.txt
*/
#define GIC_DISTR_BASE 0x8000000
#define GIC_CPUINTER_BASE 0x8010000

/* structure from https://github.com/brenns10/sos/blob/13a2d89cb8edbb45535279d2a4f07ed74c53ec91/kernel/gic.h */
/* for details see the manual: https://developer.arm.com/documentation/ihi0069/h/?lang=en */
   
typedef volatile struct __attribute__((packed)) {
	uint32_t DCTLR;        /* 0x0 Distributor Control Register */
	const uint32_t DTYPER; /* 0x4 Distributor Type Register */
	const uint32_t DIIR;   /* 0x8 Implementer Identification */
	uint32_t _reserved0[29];
	uint32_t DIGROUPR[32];   /* 0x80 - 0xFC Interrupt groupregisters */
	uint32_t DISENABLER[32]; /* 0x100 - 0x17C Interrupt set-enable registers
	                          */
	uint32_t DICENABLER[32]; /* 0x180 - 0x1FC Interrupt clear-enable
	                            registers */
	uint32_t DISPENDR[32]; /* 0x200 - 0x27C Interrupt set-pending registers
	                        */
	uint32_t DICPENDR[32]; /* 0x280 - 0x2FC Interrupt clear-pending
	                          registers */
	uint32_t DICDABR[32];  /* 0x300 - 0x3FC Active BitRegisters (GIC v1) */
	uint32_t _reserved1[32]; /* 0x380 - 0x3FC reserved on GIC v1*/
	uint32_t
	        DIPRIORITY[255]; /* 0x400 - 0x7F8 Interrupt priorityregisters */
	uint32_t _reserved2;     /* 0x7FC reserved */
	const uint32_t
	        DITARGETSRO[8];   /* 0x800 - 0x81C Interrupt CPUtargets, RO */
	uint32_t DITARGETSR[246]; /* 0x820 - 0xBF8 Interrupt CPUtargets */
	uint32_t _reserved3;      /* 0xBFC reserved */
	uint32_t DICFGR[64];      /* 0xC00 - 0xCFC Interrupt configregisters */
	/* Some PPI, SPI status registers and identification registers beyond
	   this Don't care about them */
} gic_distributor_registers;

typedef volatile struct __attribute__((packed)) {
	uint32_t CCTLR;      /* 0x0 CPU Interface controlregister */
	uint32_t CCPMR;      /* 0x4 Interrupt priority maskregister */
	uint32_t CBPR;       /* 0x8 Binary point register */
	const uint32_t CIAR; /* 0xC Interrupt acknowledgeregister */
	uint32_t CEOIR;      /* 0x10 End of interrupt register*/
	const uint32_t CRPR; /* 0x14 Running priority register*/
	const uint32_t
	        CHPPIR; /* 0x18 Higher priority pendinginterrupt register */
	uint32_t CABPR; /* 0x1C Aliased binary pointregister */
	const uint32_t CAIAR;   /* 0x20 Aliased interruptacknowledge register */
	uint32_t CAEOIR;        /* 0x24 Aliased end of interruptregister */
	const uint32_t CAHPPIR; /* 0x28 Aliased highest prioritypending
	                           interrupt register */
} gic_cpu_interface_registers;


void gic_init();
void gic_enable_interrupt(uint32_t id);
void gic_end_interrupt(uint32_t id);
void gic_register_handler(uint32_t id, gic_handler handler);
uint32_t gic_acknowledge_interrupt();
uint32_t gic_get_pending(uint32_t id);
void gic_clear_all_pending();
void gic_isr();

#endif
