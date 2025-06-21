#include "../core/hardware.h"
#include <stdint.h>

#define SERIAL_PORT 0x3F8 // port address for COM1

void
serial_init() {
    outb(SERIAL_PORT + 1, 0x00); // Disable interrupts
    outb(SERIAL_PORT + 3, 0x80); // Enable DLAB
    outb(SERIAL_PORT + 0, 0x03); // divisor low byte (38400 baud)
    outb(SERIAL_PORT + 1, 0x00); // divisor high byte
    outb(SERIAL_PORT + 3, 0x03); // 8 bits, no parity, 1 stop bit
    outb(SERIAL_PORT + 2, 0x01); // Enable FIFO, clear them, 1-byte threshold
    outb(SERIAL_PORT + 4, 0x00); // No IRQs, RTS/DSR cleared
    (void) inb(SERIAL_PORT + 5);
}

int
serial_is_transmit_empty() {
    return inb(SERIAL_PORT + 5) & 0x20;
}

void
serial_write_char(char c) {
    int timeout = 100000;
    while (serial_is_transmit_empty() == 0 && --timeout)
        ;
    outb(SERIAL_PORT, (unsigned char) c);
}

void
serial_write_str(const char* str) {
    while (*str) {
        if (*str == '\n')
            serial_write_char('\r');
        serial_write_char(*str++);
    }
}

void
serial_write_hex(uint32_t val) {
    const char* hex_chars = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        char c = hex_chars[(val >> i) & 0xF];
        serial_write_char(c);
    }
}
