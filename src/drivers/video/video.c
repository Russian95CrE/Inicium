/* video.c */

#include "video.h"
#include "../../io/stdio.h"

#define VIDEO_MEMORY ((char *)0xb8000)
int vid_pos = 0;
int res_x = 80;
int res_y = 25;

// New video driver functions
void video_driver_init(void) {
    clear();
    vid_pos = 0;
}

/*
Spend some minutes to figure out why the \n character was not breaking the line
and it was just because my stupid VGA Text Mode (0xb8000) does not automatically
move the cursor. I am really stupid.
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