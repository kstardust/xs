    .text

.macro save_register
    str lr, [sp, #-16]!
.endm


.macro restore_register
    ldr lr, [sp], #16
.endm
    
    
handle_irq:
    save_register
    bl  do_handle_irq
    restore_register
    eret

handle_sync:
    save_register
    bl  do_handle_sync
    restore_register
    eret

handle_error:
    save_register
    bl  do_handle_error
    restore_register
    eret    
    
handle_empty:
    save_register
    bl  do_handle_empty
    restore_register
    eret
        
.macro	vector	name
    .align 7        /* 128 bytes */

    mrs x28, esr_el1
    b handle_\name

1:  wfe           /* not expected to execute here */
    b 1b

.endm

    .align 7
    .global exception_table

exception_table:
    vector empty    /* Current EL with SP0 */
    vector empty
    vector empty
    vector empty
 
    vector sync     /* Current EL with SPn */
    vector irq
    vector empty 
    vector error

    vector empty    /* Lower EL using AArch64 */
    vector empty
    vector empty
    vector empty

    vector empty    /* Lower EL using AArch32 */
    vector empty
    vector empty
    vector empty
