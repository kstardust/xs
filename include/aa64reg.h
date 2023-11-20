#ifndef _AARCH64_REG
#define _AARCH64_REG

#include <params.h>

#define VA_BITS 48              /* 48-bit virtual address */

#define TG1 (2 << 30)  /* 4KB */          
#define T1_CACHE_ATTR  ((1 << 24))  /* Inner Write-Back Read-Allocate Write-Allocate Cacheable. */
#define T1SZ  ((64 - VA_BITS) << 16)

#define TG0 (0)        /* 4KB */
#define T0_CACHE_ATTR ((1 << 8))  /* Inner Write-Back Read-Allocate Write-Allocate Cacheable. */
#define T1SZ  ((64 - VA_BITS) << 16)
#define T0SZ  ((64 - VA_BITS) << 0)

#define TCR (TG1 | TG0 | T1SZ | T0SZ | T1_CACHE_ATTR | T0_CACHE_ATTR)

#define MAIR_NORMAL_WB 0xff /* Inner & Outer Write-Back Non-transient Read-Allocate Write-Allocate  */
#define MAIR_INDEX_WB 0

#define	TCR_IPS_SHIFT		32
#define	TCR_IPS_WIDTH		3

#define	TD_PAGE	       0x3
#define	TD_BLOCK       0x1
#define	TD_TABLE       0x3
#define	TD_VALID       0x1

#define TD_ATTR_SH_INNER       (3 << 8)     /* Inner Shareable */
#define	TD_ATTR_AF		  (1 << 10)    /* Access flag */
#define TD_ATTR_nG             (0 << 11)    /* non-global */ 
#define	TD_DEFAUL_ATTR  (TD_ATTR_AF | TD_ATTR_nG | TD_ATTR_SH_INNER | MAIR_INDEX_WB << 2)

#define	TD_ATTR_UXN  (1 << 54)       /* Unprivileged Execute Never */

#define	TD_TATTR_UXN  (1 << 60)     /* descriptor Unprivileged Execute Never */
#define	TD_TATTR_UAN  (1 << 61)     /* Unprivileged access not permitted. */
#define TD_TATTR_DEFAULT (TD_TATTR_UXN | TD_TATTR_UAN)

#define L0_SHIFT   39

#define L1_SHIFT   30
#define L2_SHIFT   21
#define L3_SHIFT   12

#define Ln_ENTRIES_SFHIT 9
#define Ln_ENTRIES (1 << Ln_ENTRIES_SFHIT)
#define Ln_ADDR_MASK (Ln_ENTRIES - 1)
#define Ln_TABLE_MASK ((1 << 12) - 1)


#define LOAD_ALIGN_SHIFT 21
#define LOAD_ALIGN     ((1 << LOAD_ALIGN_SHIFT) - 1)
#define LOAD_ADDR_MASK (~LOAD_ALIGN)

#define	DAIF_D			(1 << 3)
#define	DAIF_A			(1 << 2)
#define	DAIF_I			(1 << 1)
#define	DAIF_F			(1 << 0)
#define	DAIF_ALL		(DAIF_D | DAIF_A | DAIF_I | DAIF_F)
#define	DAIF_INTR		(DAIF_I)	/* All exceptions that pass */

#endif

