#ifndef PORT_H
#define PORT_H
#include <stdint.h>

static inline void
outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

#endif // PORT_H
