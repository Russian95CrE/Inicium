section .multiboot_header
    align 8
multiboot2_header:
    dd 0xE85250D6                          ; magic
    dd 0                                  ; arch (0 = i386)
    dd multiboot2_header_end - multiboot2_header  ; header length
    dd -(0xE85250D6 + 0 + (multiboot2_header_end - multiboot2_header))  ; checksum

    align 8
    ; framebuffer tag (type=5, size=24)
    dd 5
    dd 24
    dd 1024
    dd 768
    dd 32
    dd 0           ; framebuffer_type (0 = indexed, 1 = RGB, etc)
    dd 0           ; reserved/padding

    align 8
    ; end tag (type=0, size=8)
    dd 0
    dd 8

    align 8
multiboot2_header_end:

section .bss
    align 16
stack_bottom: resb 16384                  ; 16 KB stack
stack_top:

section .text
    global _start
    extern kernel_main

_start:
    mov esp, stack_top                    ; init stack
    mov esi, ebx                          ; pass multiboot info ptr
    call kernel_main                      ; enter C

.hang:
    jmp .hang
