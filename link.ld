SECTIONS
{
    . = kernaddr;
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }
    .bss (NOLOAD) : {
	. = ALIGN(8);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
	. = ALIGN(8);
        __bss_end = .;
    }
    .init_pagetable (NOLOAD) : {
        *(.init_pagetable .init_pagetable.*)
    }
    . = ALIGN(16);
    _end = .;

    /* Keep the existing 16 MiB kernel heap, now managed by Picolibc. */
    __heap_start = _end;
    __heap_end = __heap_start + 16M;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;
