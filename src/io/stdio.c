/* stdio.c */

#include "stdio.h"
#include "../drivers/video/video.h"
#include <stdarg.h>

#define PRINTF_BUF_SIZE 512

// Minimal string length function
int
strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

// Minimal integer to string conversion
void
itoa(int value, char* str) {
    char buf[16];
    int  i = 0, j = 0, is_negative = 0;
    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    if (value < 0) {
        is_negative = 1;
        value       = -value;
    }
    while (value && i < 15) {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }
    if (is_negative)
        buf[i++] = '-';
    while (i--)
        str[j++] = buf[i];
    str[j] = '\0';
}

// Minimal vsnprintf: supports %s, %d, %c
int
vsnprintf(char* buf, int size, const char* fmt, va_list args) {
    int i = 0;
    for (; *fmt && i < size - 1; fmt++) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 's') {
                const char* s = va_arg(args, const char*);
                while (*s && i < size - 1)
                    buf[i++] = *s++;
            } else if (*fmt == 'd') {
                int  d = va_arg(args, int);
                char numbuf[16];
                itoa(d, numbuf);
                const char* s = numbuf;
                while (*s && i < size - 1)
                    buf[i++] = *s++;
            } else if (*fmt == 'c') {
                char c   = (char) va_arg(args, int);
                buf[i++] = c;
            } else {
                buf[i++] = '%';
                if (i < size - 1)
                    buf[i++] = *fmt;
            }
        } else {
            buf[i++] = *fmt;
        }
    }
    buf[i] = '\0';
    return i;
}

void
printf(const char* fmt, ...) {
    char    buf[PRINTF_BUF_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, PRINTF_BUF_SIZE, fmt, args);
    va_end(args);

    char* str = buf;
    while (*str) {
        video_driver_putc(*str++);
    }
}