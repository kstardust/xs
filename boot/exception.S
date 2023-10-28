    .text


handle_irq:
    bl  do_handle_irq
    eret

handle_sync:
    bl  do_handle_sync
    eret

handle_error:
    bl  do_handle_error
    eret    
    
handle_empty:
    bl  do_handle_empty
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
