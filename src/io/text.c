#include "io/text.h"

#include "libc/string.h"

#define VID_MEM_PTR ((char *)0xb8000)
#define TERM_WIDTH 80
#define TERM_HEIGHT 25

static int cursorpos = 0;
static int backstoppos = 0;

/* light gray on black by default */
static uint8_t attr = 0x7;

void put_char(char c)
{
        switch (c) {
        case '\b':
                if (cursorpos > backstoppos) {
                        --cursorpos;
                        *(VID_MEM_PTR + cursorpos * 2) = '\0';
                        *(VID_MEM_PTR + cursorpos * 2 + 1) = attr;
                }
                break;
        case '\t':
                cursorpos += TAB_SIZE;
                break;
        case '\n':
                cursorpos += TERM_WIDTH - cursorpos % TERM_WIDTH;
                break;
        default:
                *(VID_MEM_PTR + cursorpos * 2) = c;
                *(VID_MEM_PTR + cursorpos * 2 + 1) = attr;
                ++cursorpos;
                break;
        }
        if (cursorpos > TERM_WIDTH * TERM_HEIGHT)
                scroll_text_down();
}

void put_str(const char *s)
{
        for (int i = 0; s[i] != '\0'; ++i)
                put_char(s[i]);
}

void put_hex(uint32_t h)
{
        char charmap[16] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
                'c', 'd', 'e', 'f',
        };
        put_str("0x");
        /* loop backwards to account for little endianness */
        for (int i = 3; i >= 0; --i) {
                uint8_t *b = (uint8_t *)&h + i;
                put_char(charmap[(*b & 0xf0) >> 4]);
                put_char(charmap[*b & 0xf]);
        }
}

void put_hex_64(uint64_t h)
{
        char charmap[16] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
                'c', 'd', 'e', 'f',
        };
        put_str("0x");
        /* loop backwards to account for little endianness */
        for (int i = 7; i >= 0; --i) {
                uint8_t *b = (uint8_t *)&h + i;
                put_char(charmap[(*b & 0xf0) >> 4]);
                put_char(charmap[*b & 0xf]);
        }
}

void clear_screen(void)
{
        cursorpos = 0;
        for (int i = 0; i < TERM_WIDTH * TERM_HEIGHT; ++i)
                put_char('\0');
        cursorpos = 0;
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
        backstoppos = bsp;
}

int text_cursor_pos(void)
{
        return cursorpos;
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
        memmove(VID_MEM_PTR, VID_MEM_PTR + TERM_WIDTH * 2,
                TERM_WIDTH * TERM_HEIGHT * 2 + 1);
        cursorpos -= TERM_WIDTH;
        backstoppos -= TERM_WIDTH;
}