section .multiboot_header
    align 8
multiboot2_header:
    dd 0xE85250D6                          ; magic
    dd 0                                  ; arch (0 = i386)
    dd multiboot2_header_end - multiboot2_header  ; header length
    dd -(0xE85250D6 + 0 + (multiboot2_header_end - multiboot2_header))  ; checksum

    align 8
    dw 0                                   ; end tag type
    dw 0
    dd 8                                   ; end tag size

    align 8
multiboot2_header_end:

section .text
    global _start
_start:
    ; Set up stack (16 KiB at 0x100000)
    mov rsp, 0x100000
    and rsp, ~0xF         ; Align stack to 16 bytes
    ; Move Multiboot info pointer from rsi to rdi for C calling convention
    mov rdi, rsi
    ; Pass Multiboot info pointer to kernel_main
    extern kernel_main
    call kernel_main

    ; Halt if kernel_main returns
.hang:
    hlt
    jmp .hang
