#pragma once

#include <stdarg.h>

void outw(unsigned short port, unsigned short val);
int  strcmp(const char *s1, const char *s2);
void itoa(int value, char *str);
void printf(const char *fmt, ...);
int  vsnprintf(char *buf, int size, const char *fmt, va_list args);

#ifndef NULL
#define NULL ((void *)0)
#endif