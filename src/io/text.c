#include "io/text.h"

#define VID_MEM_PTR ((char *)0xb8000)
#define TERM_WIDTH 80
#define TERM_HEIGHT 25

static int textcursorpos = 0;

/* light gray on black by default */
static uint8_t attr = 0x7;

void put_char(char c)
{
        switch (c) {
        case '\n':
                textcursorpos += TERM_WIDTH - textcursorpos % TERM_WIDTH;
                break;
        default:
                *(VID_MEM_PTR + textcursorpos * 2) = c;
                *(VID_MEM_PTR + textcursorpos * 2 + 1) = attr;
                ++textcursorpos;
                break;
        }
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

void clear_screen(void)
{
        textcursorpos = 0;

        for (int i = 0; i < TERM_WIDTH * TERM_HEIGHT; ++i)
                put_char('\0');
                
        textcursorpos = 0;
}

void log_info(const char *msg)
{
        put_str("log: ");
        put_str(msg);
        put_str("\n");
}