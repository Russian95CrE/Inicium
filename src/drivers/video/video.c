/* video.c */

#include "video.h"
#include <stdint.h>
#include <stdbool.h>

// Framebuffer info populated by kernel_main
uint32_t* framebuffer        = 0;
uint32_t  framebuffer_pitch  = 0; // bytes per line
uint32_t  framebuffer_width  = 0; // pixels per line
uint32_t  framebuffer_height = 0; // number of lines
uint8_t   framebuffer_bpp    = 0; // bits per pixel

static uint32_t cursor_x = 0; // cursor position in character cells
static uint32_t cursor_y = 0;

// Draw a single pixel at (x, y) with the given color (0xAARRGGBB)
static inline void
put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!framebuffer || x >= framebuffer_width || y >= framebuffer_height)
        return;
    uint8_t* addr     = (uint8_t*) framebuffer + y * framebuffer_pitch + x * (framebuffer_bpp / 8);
    *(uint32_t*) addr = color;
}

// Clear the entire screen to a solid color
void
video_driver_clear(uint32_t color) {
    if (!framebuffer || framebuffer_bpp != 32)
        return;
    uint32_t pitch_pixels = framebuffer_pitch / 4;
    for (uint32_t y = 0; y < framebuffer_height; y++) {
        for (uint32_t x = 0; x < framebuffer_width; x++) {
            framebuffer[y * pitch_pixels + x] = color;
        }
    }
    cursor_x = cursor_y = 0;
}

// Initialize the video driver; returns true if framebuffer is valid
bool
video_driver_init(void) {
    return framebuffer && framebuffer_bpp == 32;
}

// Draw a character as an 8x8 white block; handles newline
void
video_driver_putc(char c) {
    if (!video_driver_init())
        return;
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        uint32_t base_x = cursor_x * 8;
        uint32_t base_y = cursor_y * 8;
        for (uint32_t dy = 0; dy < 8; dy++) {
            for (uint32_t dx = 0; dx < 8; dx++) {
                put_pixel(base_x + dx, base_y + dy, 0xFFFFFFFF);
            }
        }
        cursor_x++;
    }
    // Wrap horizontally
    if (cursor_x >= framebuffer_width / 8) {
        cursor_x = 0;
        cursor_y++;
    }
    // Wrap vertically
    if (cursor_y >= framebuffer_height / 8) {
        cursor_y = 0;
    }
}

// Write a null-terminated string to screen
void
video_driver_puts(const char* s) {
    while (*s) {
        video_driver_putc(*s++);
    }
}
