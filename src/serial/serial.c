#include "../core/kernel.h"

#define SERIAL_PORT 0x3F8 // port address for COM1

void
serial_init() {
    outb(SERIAL_PORT + 1, 0x00); // Disable all interrupts
    outb(SERIAL_PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(SERIAL_PORT + 0, 0x03); // Divisor low byte (38400 baud)
    outb(SERIAL_PORT + 1, 0x00); // Divisor high byte
    outb(SERIAL_PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(SERIAL_PORT + 2, 0xC7); // Enable FIFO, clear them, 14-byte threshold
    outb(SERIAL_PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int
serial_is_transmit_empty() {
    return inb(SERIAL_PORT + 5) & 0x20;
}

void
serial_write_char(char c) {
    while (serial_is_transmit_empty() == 0)
        ;
    outb(SERIAL_PORT, c);
}

void
serial_write_str(const char* str) {
    while (*str) {
        if (*str == '\n')
            serial_write_char('\r');
        serial_write_char(*str++);
    }
}