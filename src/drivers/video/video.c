/* video.c */

#include "video.h"
#include <stdint.h>
#include <stdbool.h>

// Framebuffer info populated by kernel_main
uint32_t* framebuffer        = 0;
uint32_t  framebuffer_pitch  = 0; // bytes per scanline
uint32_t  framebuffer_width  = 0; // pixels per scanline
uint32_t  framebuffer_height = 0; // total scanlines
uint8_t   framebuffer_bpp    = 0; // bits per pixel

static uint32_t cursor_x = 0; // in character cells
static uint32_t cursor_y = 0;

// Set a pixel at (x, y) to color (0xAARRGGBB)
void
put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!framebuffer || framebuffer_bpp != 32)
        return;
    if (x >= framebuffer_width || y >= framebuffer_height)
        return;
    uint8_t* pixel     = (uint8_t*) framebuffer + y * framebuffer_pitch + x * 4;
    *(uint32_t*) pixel = color;
}

// Clear framebuffer to color
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

// Initialize driver (ensure framebuffer is valid)
bool
video_driver_init(void) {
    return framebuffer && framebuffer_bpp == 32;
}

// Simple font: 8x8 monochrome font bitmap (one byte per row) for ASCII 32..127
static const uint8_t font8x8_basic[96][8] = {
    // You can fill this with your preferred bitmap font data
};

// Draw a character c at current cursor position
enum { CHAR_W = 8,
       CHAR_H = 8 };

void
video_driver_putc(char c) {
    if (!video_driver_init())
        return;
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }
    if (c < 32 || c > 127)
        c = '?';
    const uint8_t* glyph  = font8x8_basic[c - 32];
    uint32_t       base_x = cursor_x * CHAR_W;
    uint32_t       base_y = cursor_y * CHAR_H;
    for (uint32_t row = 0; row < CHAR_H; row++) {
        for (uint32_t col = 0; col < CHAR_W; col++) {
            if (glyph[row] & (1 << col)) {
                put_pixel(base_x + col, base_y + row, 0xFFFFFFFF);
            }
        }
    }
    cursor_x++;
    if (cursor_x * CHAR_W >= framebuffer_width) {
        cursor_x = 0;
        cursor_y++;
    }
}

// Write a null-terminated string
enum { CTRL_NL = '\n' };

void
video_driver_puts(const char* s) {
    while (*s)
        video_driver_putc(*s++);
}
