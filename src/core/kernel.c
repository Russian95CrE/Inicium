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
    multiboot_info_t*            mb  = (multiboot_info_t*) mb_info;
    multiboot_tag_t*             tag = (multiboot_tag_t*) ((char*) mb + 8);
    multiboot_tag_framebuffer_t* fb  = 0;

    while (tag->type != 0) {
        if (tag->type == 5) {
            fb = (multiboot_tag_framebuffer_t*) tag;
            break;
        }
        tag = (multiboot_tag_t*) ((char*) tag + ((tag->size + 7) & ~7));
    }

    if (fb) {
        framebuffer        = (uint32_t*) fb->framebuffer_addr;
        framebuffer_pitch  = fb->framebuffer_pitch;
        framebuffer_width  = fb->framebuffer_width;
        framebuffer_height = fb->framebuffer_height;
        framebuffer_bpp    = fb->framebuffer_bpp;

        if (video_driver_init()) {
            video_driver_clear(0xFF0000FF);
            video_driver_puts("Hello, Framebuffer!\n");
            video_driver_puts("Inicium carregado.");
        }

        while (1)
            __asm__("hlt");
    }

    while (1)
        __asm__("hlt");
}