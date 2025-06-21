#pragma once

void
serial_init();
int
serial_is_transmit_empty();
void
serial_write_char(char c);
void
serial_write_str(const char* str);
void
serial_write_hex(uint32_t val);