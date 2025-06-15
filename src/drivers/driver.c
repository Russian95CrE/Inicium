/* driver.c */

#include "driver.h"

#define VIDEO_MEMORY ((char *)0xb8000)
int vid_pos = 0;
int res_x = 80;
int res_y = 25;

// new video driver functions
void video_driver_init(void) {
    // clear the screen using video memory
    char *video = VIDEO_MEMORY;
    for (int i = 0; i < res_x * res_y; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }
    vid_pos = 0;
}

/*
spend some minutes to figure out why the \n character was not breaking the line
and it was just because my stupid VGA Text Mode (0xb8000) does not
automatically move the cursor '-'
*/
void video_driver_putc(char c) {
    char *video = VIDEO_MEMORY;
    if (c == '\n') {
        vid_pos += res_x - (vid_pos % res_x); // move to start of next line
    } else {
        video[vid_pos * 2] = c;
        video[vid_pos * 2 + 1] = 0x07;
        vid_pos = (vid_pos + 1) % (res_x * res_y);
    }
}

// updated driver functions using the video driver
void driver_init(void) {
    video_driver_init();
    // ...existing initialization code if needed...
}

void driver_run(void) {
    // For demonstration, the video driver doesn't update automatically.
    // You can use video_driver_putc() for additional output if desired.
    // ...existing code...
}