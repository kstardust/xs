#ifndef _AARCH64_REG
#define _AARCH64_REG

#include <params.h>

#define VA_BITS 48              /* 48-bit virtual address */

#define TG1 (2 << 30)  /* 4KB */          
#define T1_CACHE_ATTR  ((1 << 24))  /* Inner Write-Back Read-Allocate Write-Allocate Cacheable. */
#define T1SZ  ((64 - VA_BITS) << 16)

#define TG0 (0)   /* 4KB */
#define T0_CACHE_ATTR ((1 << 8))  /* Inner Write-Back Read-Allocate Write-Allocate Cacheable. */
#define T0SZ  ((64 - VA_BITS) << 16)

#define TCR (TG1 | TG0 | T1SZ | T0SZ | T1_CACHE_ATTR | T0_CACHE_ATTR)

#define MAIR_NORMAL_WB 0xff /* Inner & Outer Write-Back Non-transient Read-Allocate Write-Allocate  */
#define MAIR_INDEX_WB 0

#define	TCR_IPS_SHIFT		32
#define	TCR_IPS_WIDTH		3

#endif
