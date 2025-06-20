#include "commands.h"
#include "../drivers/video/video.h"
#include <stdbool.h>
#include <stdio.h>

bool clear(void) {
    char *video = (char *)0xb8000;
    for (int i = 0; i < res_x * res_y * 2; i += 2) {
        video[i]     = ' ';
        video[i + 1] = 0x07;
    }
    vid_pos = 0; // Reset cursor position
}

bool poweroff(void) {
    // Yes.
    static bool did_poweroff = false;
    if (did_poweroff) {
        printf("hmmmm placeholder poweroff\n");
    }
}