#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

void
video_init();
void
video_clear();
void
video_putc(char c);
void
video_puts(const char* str);
void
video_set_cursor(uint8_t x, uint8_t y);

// Aliases for compatibility with other code
#define video_driver_init video_init
#define video_driver_clear video_clear
#define video_driver_putc video_putc
#define video_driver_puts video_puts

#endif // VIDEO_H
