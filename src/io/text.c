#include "io/text.h"

#define VID_MEM_PTR ((char *)0xb8000)
#define TERM_WIDTH  80
#define TERM_HEIGHT 25

static int text_cursor_pos = 0;

void put_char(char c)
{
        *(VID_MEM_PTR + text_cursor_pos * 2) = c;
        ++text_cursor_pos;
}

void put_str(const char *s)
{
        for (int i = 0; s[i] != '\0'; ++i) {
                switch (s[i]) {
                case '\n':
                        text_cursor_pos += TERM_WIDTH -
                                           text_cursor_pos % TERM_WIDTH;
                        
                        break;
                default:
                        put_char(s[i]);
                        break;
                }
        }
}

void clear_screen(void)
{
        text_cursor_pos = 0;

        for (int i = 0; i < TERM_WIDTH + TERM_HEIGHT; ++i)
                put_char('\0');

        text_cursor_pos = 0;
}