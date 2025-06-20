#pragma once
#include <stdint.h>
#include <stdbool.h>

extern uint32_t* framebuffer;
extern uint32_t  framebuffer_pitch;
extern uint32_t  framebuffer_width;
extern uint32_t  framebuffer_height;
extern uint8_t   framebuffer_bpp;

static inline void
put_pixel(uint32_t x, uint32_t y, uint32_t color);
bool
video_driver_init(void);
void
video_driver_clear(uint32_t color);
void
video_driver_putc(char c);
void
video_driver_puts(const char* s);
