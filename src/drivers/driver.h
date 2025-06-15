#pragma once

void video_driver(void);
void driver_init(void);
void driver_run(void);

// new video driver interface
void video_driver_init(void);
void video_driver_putc(char c);
void print(const char *str);

extern int res_x;
extern int res_y;
