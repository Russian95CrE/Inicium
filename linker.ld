ENTRY(_start)

SECTIONS {
    . = 1M;

    .text ALIGN(8) : {
        /* Força header multiboot2 no início e com alinhamento */
        KEEP(*(.multiboot_header))
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data   : { *(.data*) }
    .bss    : { *(.bss*) }
}
