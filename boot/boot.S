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

    bl start_mmu

    /* switch to virtual address space */
    ldr x1, vmdone_addr
    br  x1      

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

4:  bl      get_virt_delta
        
    msr	vbar_el1, x2
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


start_mmu:
    adrp	x2, exception_table
    add x2, x2, :lo12:exception_table
    
    tlbi vmalle1
    msr ttbr0_el1, x1

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

stack_start:
    .space KERN_STACK_SIZE
stack_end:
