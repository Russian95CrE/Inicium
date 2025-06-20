section .text
align 8
multiboot2_header:
    dd 0xE85250D6         ; magic
    dd 0                  ; architecture
    dd 40                 ; total size of header in bytes
    dd 0x100000000 - (0xE85250D6 + 0 + 40) ; checksum

    ; framebuffer tag
    dw 5
    dw 0
    dd 20
    dd 1024
    dd 768
    dd 32

    ; end tag
    dw 0
    dw 0
    dd 8

align 8
multiboot2_header_end:

global _start
extern kernel_main

_start:
    mov esi, ebx
    call kernel_main

.hang:
    jmp .hang
