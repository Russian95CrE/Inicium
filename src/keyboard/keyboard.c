/* keyboard.c */

#include "keyboard.h"
#include "../io/io.h"

#define PORT_KEYBOARD_DATA 0x60
#define PORT_KEYBOARD_STATUS 0x64

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// Basic scancode-to-ASCII mapping (US layout, partial).
static const char scancode_to_ascii[128] = {
    0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,   'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\','z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0,   '*', 0,   ' ', 0,   /* remaining unmapped keys zeroed */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void keyboard_init(void) {
    print("[keyboard] initialized\n");
}

char keyboard_getchar(void) {
    unsigned char scancode;
    char ascii;
    while (1) {
        // Wait until keyboard status register indicates data is available.
        while (!(inb(PORT_KEYBOARD_STATUS) & 0x01)) {
            // ...waiting for key data...
        }
        scancode = inb(PORT_KEYBOARD_DATA);
        // Ignore key release scancodes.
        if (scancode & 0x80) continue;
        ascii = scancode_to_ascii[scancode];
        if (ascii) {
            return ascii;
        }
        // If unmapped (ascii is 0), continue polling.
    }
}