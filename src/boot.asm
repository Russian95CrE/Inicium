section .multiboot_header
    align 8
multiboot2_header:
    dd 0xE85250D6                          ; magic
    dd 0                                    ; arch (0 = i386)
    dd multiboot2_header_end - multiboot2_header  ; header length
    dd -(0xE85250D6 + 0 + (multiboot2_header_end - multiboot2_header))  ; checksum

    align 8
    dw 5                                   ; type framebuffer
    dw 1                                   ; flags (1 = required)
    dd 28                                  ; size tag (FIX: 28 bytes)
    dd 1024                                ; width
    dd 768                                 ; height
    dd 32                                  ; bpp
    dd 0                                   ; framebuffer_type (0 = indexed)
    dd 0                                   ; reserved/padding

    align 8
    dd 0                                   ; end tag type
    dd 8                                   ; end tag size

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
