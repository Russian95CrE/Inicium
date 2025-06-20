ENTRY(_start)

SECTIONS {
    . = 1M;

    .multiboot_header ALIGN(8) : {
        KEEP(*(.multiboot_header))
    }

    .text ALIGN(8) : {
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data   : { *(.data*) }
    .bss    : { *(.bss*) }
}
