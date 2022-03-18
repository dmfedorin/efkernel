#include "shell/shell.h"

#include "libc/string.h"

#define SHELL_BUF_SIZE 1024

static char shellbuf[SHELL_BUF_SIZE] = { 0 };

void write_shell_buf(char c)
{
        switch (c) {
        case '\b':
                break;
        default:
                strncat(shellbuf, &c, 1);
                break;
        }
}