#pragma once

extern int vid_pos;
extern int res_x;
extern int res_y;

void video_driver_init(void);
void video_driver_putc(char c);