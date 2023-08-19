.section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

.global _start  // Execution starts here

.global loadaddr
.set loadaddr, 0x2000


_start:
    .align 2
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // We're not on the main core, so hang in an infinite wait loop
1:  wfe
    b       1b
2:  // We're on the main core!

    // Set stack to start below our code
    adrp    x1, __stack_end
    add     x1, x1, :lo12:__stack_end
    mov     sp, x1

    // Clean the BSS section
    ldr     x1, =__bss_start     // Start address
    ldr     w2, =__bss_size      // Size of the section
3:  cbz     w2, 4f               // Quit loop if zero
    str     xzr, [x1], #8
    
    sub     w2, w2, #1
    cbnz    w2, 3b               // Loop if non-zero

    // Jump to our main() routine in C (make sure it doesn't return)
4:  bl      get_virt_delta
    bl 	    c_start
    mov     x28, #0xf
    wfe
    // In case it does return, halt the master core too
    b       1b


get_virt_delta:
    .align 2
    adrp    x1, virt_addr
    add     x1, x1, :lo12:virt_addr
    ldr     x2, [x1]
    ret    
virt_addr:  
    .quad virt_addr            
