// video.c

#include "video.h"
#include <stdint.h>
#include <stdbool.h>

uint32_t* framebuffer        = 0;
uint32_t  framebuffer_pitch  = 0;
uint32_t  framebuffer_width  = 0; // pixels
uint32_t  framebuffer_height = 0; // pixels
uint8_t   framebuffer_bpp    = 0; // bits per pixel

static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;

static inline void
put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!framebuffer || x >= framebuffer_width || y >= framebuffer_height)
        return;

    uint8_t* pixel_addr     = (uint8_t*) framebuffer + y * framebuffer_pitch + x * 4;
    *(uint32_t*) pixel_addr = color;
}

bool
video_driver_init(void) {
    return framebuffer != 0 && framebuffer_bpp == 32;
}

void
video_driver_clear(uint32_t color) {
    uint32_t pitch = framebuffer_pitch / 4;
    for (uint32_t y = 0; y < framebuffer_height; y++) {
        for (uint32_t x = 0; x < framebuffer_width; x++) {
            framebuffer[y * pitch + x] = color;
        }
    }
    cursor_x = cursor_y = 0;
}

void
video_driver_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        put_pixel(cursor_x * 8, cursor_y * 8, 0xFFFFFFFF); // white
        cursor_x++;
    }

    // wrap
    if (cursor_x >= framebuffer_width / 8) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= framebuffer_height / 8) {
        cursor_y = 0;
    }
}

void
video_driver_puts(const char* s) {
    while (*s) {
        video_driver_putc(*s++);
    }
}
