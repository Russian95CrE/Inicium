/* commands.c */

#include "commands.h"
#include "../core/kernel.h"
#include "../drivers/video/video.h"
#include <stdbool.h>

void
clear() {
    video_driver_clear();
}

void
poweroff(void) {
    // Try to power off using ACPI (works in QEMU/Bochs)
    // Out to port 0x604 with value 0x2000
    outw(0x604, 0x2000);

    // Fallback: halt the CPU
    while (1) {
        __asm__ __volatile__("hlt");
    }
}

void
reboot(void) {
    // Try to reboot using the keyboard controller
    __asm__ __volatile__("cli");
    outb(0x64, 0xFE);
    while (1) {
        __asm__ __volatile__("hlt");
    }
}