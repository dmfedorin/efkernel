#include "io/text.h"

#include <stdint.h>

#define VID_MEM_PTR ((char *)0xb8000)
#define TERM_WIDTH 80
#define TERM_HEIGHT 25

static int textcursorpos = 0;

/* light gray on black by default */
static uint8_t attr = 0x7;

void put_char(char c)
{
        *(VID_MEM_PTR + textcursorpos * 2) = c;
        *(VID_MEM_PTR + textcursorpos * 2 + 1) = attr;
        ++textcursorpos;
}

void put_str(const char *s)
{
        for (int i = 0; s[i] != '\0'; ++i) {
                switch (s[i]) {
                case '\n':
                        textcursorpos += TERM_WIDTH -
                                         textcursorpos % TERM_WIDTH;
                        break;
                case '\r':
                        attr = (uint8_t)s[i + 1];
                        ++i;
                        break;
                default:
                        put_char(s[i]);
                        break;
                }
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