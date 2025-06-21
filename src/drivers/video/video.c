#include "video.h"
#include <stddef.h>
#include "port.h" // For outb declaration

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static uint16_t* const vga_buffer = (uint16_t*) VGA_ADDRESS;
static uint8_t         cursor_x   = 0;
static uint8_t         cursor_y   = 0;
static uint8_t         vga_color  = 0x07; // Light grey on black

static void
update_cursor() {
    uint16_t pos = (uint16_t) (cursor_y * VGA_WIDTH + cursor_x);
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void
video_init() {
    video_clear();
    video_set_cursor(0, 0);
}

void
video_clear() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = ((uint16_t) vga_color << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}

void
video_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else {
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = ((uint16_t) vga_color << 8) | c;
        cursor_x++;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    if (cursor_y >= VGA_HEIGHT) {
        for (size_t y = 1; y < VGA_HEIGHT; y++) {
            for (size_t x = 0; x < VGA_WIDTH; x++) {
                vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
            }
        }
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = ((uint16_t) vga_color << 8) | ' ';
        }
        cursor_y = VGA_HEIGHT - 1;
    }
    update_cursor();
}

void
video_puts(const char* str) {
    while (*str) {
        video_putc(*str++);
    }
}

void
video_set_cursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
    update_cursor();
}
