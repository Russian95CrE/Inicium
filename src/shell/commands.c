/* commands.c */

#include "commands.h"
#include "../core/kernel.h"
#include "../drivers/video/video.h"
#include <stdbool.h>

bool clear(void) {
    char *video = (char *)0xb8000;
    for (int i = 0; i < res_x * res_y * 2; i += 2) {
        video[i]     = ' ';
        video[i + 1] = 0x07;
    }
    vid_pos = 0; // Reset cursor position
}

bool poweroff(void) {
    // Try to power off using ACPI (works in QEMU/Bochs)
    // Out to port 0x604 with value 0x2000
    outw(0x604, 0x2000);

    // Fallback: halt the CPU
    while (1) {
        __asm__ __volatile__("hlt");
    }
    return true; // Not reached
}