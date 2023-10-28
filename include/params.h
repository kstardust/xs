#ifndef _PARAMS
#define _PARAMS

#define KERN_MAX_ADDR 0xffff000080000000      
#define KERN_MIN_ADDR 0xffff000000000000 /* 2GB */

#define USER_MAX_ADDR 0x0000100000000000 
#define USER_MIN_ADDR 0x0000000000000000 /* 16TB */

#define PAGE_SHIFT        12                /* 4k */
#define PAGE_SIZE         (1 << PAGE_SHIFT)
#define PAGE_SIZE_MASK    (PAGE_SIZE - 1)

#define KERN_STACK_SIZE    (PAGE_SIZE)

#endif
