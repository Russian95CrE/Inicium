/* video.c */

#include "video.h"
#include "../../io/stdio.h"

#define VIDEO_MEMORY ((char*) 0xb8000)
int vid_pos = 0;
int res_x   = 80;
int res_y   = 25;

// Set hardware cursor position
void
set_hw_cursor(int pos) {
    unsigned short cursor = (unsigned short) pos;
    outw(0x3D4, 0x0F);
    outw(0x3D5, cursor & 0xFF);
    outw(0x3D4, 0x0E);
    outw(0x3D5, (cursor >> 8) & 0xFF);
}

void
reset_hw_cursor(void) {
    vid_pos = 0;
    // Reset hardware cursor as well
    extern void outw(unsigned short port, unsigned short val);
    outw(0x3D4, 0x0F);
    outw(0x3D5, 0);
    outw(0x3D4, 0x0E);
    outw(0x3D5, 0);
}

// New video driver functions
bool
video_driver_init(void) {
    if (VIDEO_MEMORY == NULL) {
    }
    vid_pos = 0;
    set_hw_cursor(vid_pos);
}

/*
Spend some minutes to figure out why the \n character was not breaking the line
and it was just because my stupid VGA Text Mode (0xb8000) does not automatically
move the cursor. I am really stupid.
*/
void
video_driver_putc(char c) {
    char* video = VIDEO_MEMORY;
    if (c == '\n') {
        vid_pos += res_x - (vid_pos % res_x); // move to start of next line
        if (vid_pos >= res_x * res_y) {
            vid_pos = (res_y - 1) * res_x;
            // Optionally: scroll screen up here
        }
    } else {
        video[vid_pos * 2]     = c;
        video[vid_pos * 2 + 1] = 0x07;
        vid_pos++;
        if (vid_pos >= res_x * res_y) {
            vid_pos = (res_y - 1) * res_x;
            // Optionally: scroll screen up here
        }
    }
    set_hw_cursor(vid_pos);
}