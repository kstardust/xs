.section ".text.boot" 

#include <params.h>
#include <aa64reg.h>
    
.global _start


/* A peculiar pitfall:
 *
 * When we use the ELF format as the input to the QEMU kernel option, QEMU will load the
 * ELF file exactly at kernaddr. Lets say the kernaddr is 0x2000, according to
 * (https://www.qemu.org/docs/master/system/arm/virt.html), the RAM starts at 0x40000000.
 * I assume QEMU loaded the ELF to the ROM (you can verify that with info mtree in the QEMU
 * monitor), and the stack, which is located immediately after the ELF file, is also in ROM.
 * All stack operations will fail quietly.
 */
    
.global kernaddr
.set kernaddr, 0x40000000 // KERN_MIN_ADDR


_start:
    .align 2

    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    /* other cores will hang in an infinite wait loop */
1:  wfe
    b       1b
2:  /* main core */

    bl      get_virt_delta
 
    bl      build_page_table
    
    bl      start_mmu

    /* switch to virtual address space */
    ldr     x1, vmdone_addr
    br      x1      

vmdone:
    /* Set stack to start below our code */    
    adrp    x1, stack_end
    add     x1, x1, :lo12:stack_end
    mov     sp, x1
    
    /* init bss */
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, 4f
    
    str     xzr, [x1], #8
    
    sub     w2, w2, #1
    cbnz    w2, 3b               

    bl 	    c_start
    
4:  msr	    vbar_el1, x2
    svc     0
    bl 	    c_start
    svc     0    
    bl 	    c_start
    svc     0
    mov     x28, #0xf
    
    wfe
    b       1b
    
vmdone_addr:
    .quad vmdone
    

build_page_table:

    /* Save LR */
    mov x28, x30
    
    /* x27: PA - VA */
    adrp x10, page_table_el0_l1
    add x10, x10, :lo12:page_table_el0_l1

    mov x8, #(kernaddr)
    add x7, x8, x27
    mov x9, #1
    
    /* VA == PA L1 */
    bl build_l1_block

    mov x7, x10
    add x10, x10, #(PAGE_SIZE)

    /* VA == PA L0 */
    bl link_l0_table

    /* Restore LR*/
    mov x30, x28
    
    ret

build_l1_block:
    /*
        x7 PA start
        x8 VA start
        x9 entry count
        x10 table address
    */

    /* attributes */
    mov x11, #(TD_BLOCK)
    orr x11, x11, #(TD_DEFAUL_ATTR)
    orr x11, x11, #(TD_ATTR_UXN)

    /* index */    
    lsr x12, x8, #(L1_SHIFT)
    and x12, x12, #(Ln_ADDR_MASK)

    /* output PA */
    lsr x7, x7, #(L1_SHIFT)
    
1:  orr x13, x11, x7, lsl #(L1_SHIFT)
    str x13, [x10, x12, lsl #3]

    sub x9, x9, #1
    add x7, x7, #1
    add x12, x12, #1
    
    cbnz x9, 1b

    ret

build_l2_block:
    /*
        x7 PA start
        x8 VA start
        x9 entry count
        x10 table address
    */

    /* attributes */
    mov x11, #(TD_BLOCK)
    orr x11, x11, #(TD_DEFAUL_ATTR)
    orr x11, x11, #(TD_ATTR_UXN)

    /* index */    
    lsr x12, x8, #(L2_SHIFT)
    and x12, x12, #(Ln_ADDR_MASK)

    /* output PA */
    lsr x7, x7, #(L2_SHIFT)
    
1:  orr x13, x11, x7, lsl #(L2_SHIFT)
    str x13, [x10, x12, lsl #3]

    sub x9, x9, #1
    add x7, x7, #1
    add x12, x12, #1
    
    cbnz x9, 1b

    ret

    
link_l0_table:
    /*
        x7 PA start(L1 table)
        x8 VA start
        x10 table address
    */

    /* attributes */
    mov x11, #(TD_TABLE)
    orr x11, x11, #(TD_TATTR_DEFAULT)

    /* index */
    lsr x12, x8, #(L0_SHIFT)
    and x12, x12, #(Ln_ADDR_MASK)

    /* output PA (L1 table PA) */
    lsr x7, x7, #(PAGE_SHIFT)

    orr x13, x11, x7, lsl #(PAGE_SHIFT)
    str x13, [x10, x12, lsl #3]

    ret

link_l1_table:
    /*
        x7 PA start(L2 table)
        x8 VA start
        x10 table address
    */

    /* attributes */
    mov x11, #(TD_TABLE)
    orr x11, x11, #(TD_TATTR_DEFAULT)

    /* index */
    lsr x12, x8, #(L1_SHIFT)
    and x12, x12, #(Ln_ADDR_MASK)

    /* output PA (L2 table PA) */
    lsr x7, x7, #(PAGE_SHIFT)

    orr x13, x11, x7, lsl #(PAGE_SHIFT)
    str x13, [x10, x12, lsl #3]

    ret
    

start_mmu:
    adrp	x2, exception_table
    add x2, x2, :lo12:exception_table

    tlbi vmalle1

    adrp x1, page_table_el0_l0
    add x1, x1, :lo12:page_table_el0_l0
    msr ttbr0_el1, x1

    adrp x1, page_table_el1_l0
    add x1, x1, :lo12:page_table_el1_l0
    msr ttbr1_el1, x1

    ldr x2, tcr

    mrs	x3, id_aa64mmfr0_el1
	/* Copy the IPS from id_aa64mmfr0_el1 into TCR.IPS (PARange) */
    bfi	x2, x3, #(TCR_IPS_SHIFT), #(TCR_IPS_WIDTH)
    msr tcr_el1, x2 
    isb

    ldr x2, mair
    msr mair_el1, x2

    mrs x0, sctlr_el1
    orr x0, x0, #1
    msr sctlr_el1, x0
    isb

    ret

mair:
    .quad MAIR_NORMAL_WB
tcr:
    .quad TCR

    
get_virt_delta:
    .align 2
    adrp    x1, virt_addr
    add     x1, x1, :lo12:virt_addr
    ldr     x2, [x1]
    sub     x27, x1, x2               /* DELTA(x27) = PA(x2) - VA(x1) */
    ret
virt_addr:  
    .quad virt_addr            

.bss
    .align PAGE_SHIFT

/* VA == PA table */
page_table_el0_l1:
    .space PAGE_SIZE
page_table_el0_l0:
    .space PAGE_SIZE

/* kernel virtual map */
page_table_el1_l2:
    .space PAGE_SIZE
page_table_el1_l1:
    .space PAGE_SIZE
page_table_el1_l0:
    .space PAGE_SIZE

stack_start:
    .space KERN_STACK_SIZE
stack_end:
