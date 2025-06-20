#pragma once

extern int vid_pos;
extern int res_x;
extern int res_y;

void
set_hw_cursor(int pos);
void
reset_hw_cursor(void);

bool
video_driver_init(void);
void
video_driver_putc(char c);