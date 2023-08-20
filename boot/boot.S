.section ".text.boot" 

.global _start


/* A peculiar pitfall:
 *
 * When we use the ELF format as the input to the QEMU kernel option, QEMU will load the
 * ELF file exactly at (kernaddr) lets say the kernaddr is 0x2000, according to
 * (https://www.qemu.org/docs/master/system/arm/virt.html), the RAM starts at 0x40000000.
 * I assume QEMU will loaded the ELF to the ROM (you can verify that with info mtree in the QEMU
 * monitor), and the stack, which is located immediately after the ELF file, is also in ROM.
 * All stack operations will fail quietly.
 */
    
.global kernaddr
.set kernaddr, 0x2000


_start:
    .align 2

    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    /* other cores will hang in an infinite wait loop */
1:  wfe
    b       1b
2:  /* main core */

    /* Set stack to start below our code */
    adrp    x1, __stack_end
    add     x1, x1, :lo12:__stack_end
    mov     sp, x1

    /* init bss */
    ldr     x1, =__bss_start     
    ldr     w2, =__bss_size      
3:  cbz     w2, 4f               
    str     xzr, [x1], #8
    
    sub     w2, w2, #1
    cbnz    w2, 3b               


4:  bl      get_virt_delta
    
	adrp	x2, exception_table
    add x2, x2, :lo12:exception_table
    
	msr	vbar_el1, x2
    svc     0
    bl 	    c_start
    svc     0    
    bl 	    c_start
    svc     0
    mov     x28, #0xf
    
    wfe
    b       1b

get_virt_delta:
    .align 2
    adrp    x1, virt_addr
    add     x1, x1, :lo12:virt_addr
    ldr     x2, [x1]    
    sub     x27, x1, x2               /* DELTA(x27) = PA(x2) - VA(x1) */
    ret
virt_addr:  
    .quad virt_addr            
