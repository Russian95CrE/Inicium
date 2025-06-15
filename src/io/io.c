/* io.c */

#include "io.h"
#include "../drivers/driver.h"

void print(const char *str) {
    while (*str) {
        video_driver_putc(*str++);
    }
}

void clear(void) {
    char *video = (char *)0xb8000;
    for (int i = 0; i < res_x * res_y * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = 0x07;
    }
}