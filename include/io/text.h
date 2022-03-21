#ifndef TEXT_H_Z7XdCAV1LeJvBsDilbLT9PJ6ElTo9KL8
#define TEXT_H_Z7XdCAV1LeJvBsDilbLT9PJ6ElTo9KL8

#include <stdint.h>

#define TAB_SIZE 8

void put_char(char c);
void put_str(const char *s);
void put_hex(uint32_t h);
void put_hex_64(uint64_t h);
void clear_screen(void);
void log_info(const char *msg);
void set_text_back_stop_pos(int bsp);
int text_cursor_pos(void);

#endif