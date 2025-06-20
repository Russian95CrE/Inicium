#include <stdint.h>
#include <stdbool.h>
#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../drivers/video/video.h"
#include "../shell/commands.h"
#include "../shell/inish.h"
#include "../serial/serial.h"
#include "multiboot.h"
#include "../io/inicium.h"

void
outw(unsigned short port, unsigned short val) {
    __asm__ __volatile__("outw %0, %1" : : "a"(val), "Nd"(port));
}

void
outb(unsigned short port, unsigned char val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char
inb(unsigned short port) {
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void
kernel_main(void* mb_info) {
    serial_init();
    serial_write_str("Kernel started\n");

    multiboot_tag_t*             tag = (multiboot_tag_t*) ((uint8_t*) mb_info + 8);
    multiboot_tag_framebuffer_t* fb  = NULL;

    while (tag->type != 0) {
        serial_write_str("Checking multiboot tag type: ");
        // print hex tag type (simplified)
        unsigned int type = tag->type;
        char         hex[9];
        for (int i = 7; i >= 0; i--) {
            int val = type & 0xF;
            hex[i]  = val < 10 ? '0' + val : 'A' + (val - 10);
            type >>= 4;
        }
        hex[8] = 0;
        serial_write_str(hex);
        serial_write_str("\n");

        if (tag->type == 5) {
            serial_write_str("Framebuffer tag found\n");
            sleep(10000);
            fb = (multiboot_tag_framebuffer_t*) tag;
            break;
        }

        tag = (multiboot_tag_t*) ((uint8_t*) tag + ((tag->size + 7) & ~7));
    }

    if (fb) {
        framebuffer        = (uint32_t*) (uintptr_t) fb->framebuffer_addr;
        framebuffer_pitch  = fb->framebuffer_pitch;
        framebuffer_width  = fb->framebuffer_width;
        framebuffer_height = fb->framebuffer_height;
        framebuffer_bpp    = fb->framebuffer_bpp;

        serial_write_str("Clearing screen...\n");
        put_pixel(framebuffer_width / 2, framebuffer_height / 2, 0xFFFFFFFF);

        serial_write_str("Halted.\n");
        while (1)
            __asm__("hlt");
    } else {
        serial_write_str("[PANIC] Framebuffer not found\n");
        sleep(5000);
        poweroff();
    }
}
