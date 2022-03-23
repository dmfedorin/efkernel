#include "io/text.h"

#include "libc/string.h"

#define VIDEO_MEM_PTR ((char *)0xb8000)
#define TERM_WIDTH 80
#define TERM_HEIGHT 25

static int cursor_pos = 0;
static int back_stop_pos = 0;

/* light gray on black by default */
static uint8_t attr = 0x7;

void put_char(char c)
{
        switch (c) {
        case '\b':
                if (cursor_pos > back_stop_pos) {
                        --cursor_pos;
                        *(VIDEO_MEM_PTR + cursor_pos * 2) = '\0';
                        *(VIDEO_MEM_PTR + cursor_pos * 2 + 1) = attr;
                }
                break;
        case '\t':
                cursor_pos += TAB_SIZE;
                break;
        case '\n':
                cursor_pos += TERM_WIDTH - cursor_pos % TERM_WIDTH;
                break;
        default:
                *(VIDEO_MEM_PTR + cursor_pos * 2) = c;
                *(VIDEO_MEM_PTR + cursor_pos * 2 + 1) = attr;
                ++cursor_pos;
                break;
        }
        if (cursor_pos > TERM_WIDTH * TERM_HEIGHT)
                scroll_text_down();
}

void put_str(const char *s)
{
        for (int i = 0; s[i] != '\0'; ++i)
                put_char(s[i]);
}

void put_hex(uint32_t h)
{
        char char_map[16] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
                'c', 'd', 'e', 'f',
        };
        put_str("0x");
        /* loop backwards to account for little endianness */
        for (int i = 3; i >= 0; --i) {
                uint8_t *b = (uint8_t *)&h + i;
                put_char(char_map[(*b & 0xf0) >> 4]);
                put_char(char_map[*b & 0xf]);
        }
}

void put_hex_64(uint64_t h)
{
        char char_map[16] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
                'c', 'd', 'e', 'f',
        };
        put_str("0x");
        /* loop backwards to account for little endianness */
        for (int i = 7; i >= 0; --i) {
                uint8_t *b = (uint8_t *)&h + i;
                put_char(char_map[(*b & 0xf0) >> 4]);
                put_char(char_map[*b & 0xf]);
        }
}

void clear_screen(void)
{
        cursor_pos = 0;
        for (int i = 0; i < TERM_WIDTH * TERM_HEIGHT; ++i)
                put_char('\0');
        cursor_pos = 0;
        set_text_back_stop_pos(0);
}

void log_info(const char *msg)
{
        put_str("log: ");
        put_str(msg);
        put_char('\n');
}

void set_text_back_stop_pos(int bsp)
{
        back_stop_pos = bsp;
}

int text_cursor_pos(void)
{
        return cursor_pos;
}

void set_text_attr(enum text_color fg, enum text_color bg)
{
        attr = bg << 4 | fg;
}

enum text_color text_bg_color(void)
{
        return attr >> 4;
}

enum text_color text_fg_color(void)
{
        return attr & 0xf;
}

/* scrolling will lose information */
void scroll_text_down(void)
{
        memmove(VIDEO_MEM_PTR, VIDEO_MEM_PTR + TERM_WIDTH * 2,
                TERM_WIDTH * TERM_HEIGHT * 2 + 1);
        cursor_pos -= TERM_WIDTH;
        back_stop_pos -= TERM_WIDTH;
}