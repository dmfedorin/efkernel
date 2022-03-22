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

enum text_color {
        TEXT_COLOR_BLACK = 0x0,
        TEXT_COLOR_BLUE = 0x1,
        TEXT_COLOR_GREEN = 0x2,
        TEXT_COLOR_CYAN = 0x3,
        TEXT_COLOR_RED = 0x4,
        TEXT_COLOR_MAGENTA = 0x5,
        TEXT_COLOR_BROWN = 0x6,
        TEXT_COLOR_LIGHT_GRAY = 0x7,
        TEXT_COLOR_GRAY = 0x8,
        TEXT_COLOR_LIGHT_BLUE = 0x9,
        TEXT_COLOR_LIGHT_GREEN = 0xa,
        TEXT_COLOR_LIGHT_CYAN = 0xb,
        TEXT_COLOR_LIGHT_RED = 0xc,
        TEXT_COLOR_LIGHT_MAGENTA = 0xd,
        TEXT_COLOR_LIGHT_BROWN = 0xe,
        TEXT_COLOR_WHITE = 0xf,
};

void set_text_attr(enum text_color fg, enum text_color bg);
enum text_color text_bg_color(void);
enum text_color text_fg_color(void);

#endif