#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../drivers/video/video.h"
#include "../shell/inish.h"
#include <stdint.h>
#include "multiboot.h"

void
outw(unsigned short port, unsigned short val) {
    __asm__ __volatile__("outw %0, %1" : : "a"(val), "Nd"(port));
}

void
outb(unsigned short port, unsigned char val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Kernel entrypoint
void
kernel_main(void* mb_info) {
    multiboot_tag_t*             tag = (multiboot_tag_t*) ((uint8_t*) mb_info + 8);
    multiboot_tag_framebuffer_t* fb  = 0;

    while (tag->type != 0) {
        if (tag->type == 5) {
            fb = (multiboot_tag_framebuffer_t*) tag;
            break;
        }

        // Alinha o ponteiro da próxima tag (Multiboot2 exige alinhamento de 8 bytes)
        tag = (multiboot_tag_t*) ((uint8_t*) tag + ((tag->size + 7) & ~7));
    }

    if (fb) {
        framebuffer        = (uint32_t*) (uintptr_t) fb->framebuffer_addr;
        framebuffer_pitch  = fb->framebuffer_pitch;
        framebuffer_width  = fb->framebuffer_width;
        framebuffer_height = fb->framebuffer_height;
        framebuffer_bpp    = fb->framebuffer_bpp;

        while (1)
            __asm__("hlt");
    }

    // Caso não tenha framebuffer
    while (1)
        __asm__("hlt");
}
