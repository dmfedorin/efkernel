#include "shell/shell.h"

#include "io/ps2kb.h"
#include <stdbool.h>
#include "io/text.h"
#include "libc/string.h"
#include "libc/ctype.h"
#include "shell/defcmd.h"
#include "defs.h"
#include "kernel.h"

#define SHELL_BUF_SIZE 256
#define LEX_BUF_SIZE 256
#define MAX_ARGS 64

static char shellbuf[SHELL_BUF_SIZE] = { 0 };
static int cursorpos = 0;

static void put_shell_buf_char(char c)
{
        switch (c) {
        case '\b':
                if (cursorpos > 0) {
                        shellbuf[cursorpos] = '\0';
                        --cursorpos;
                }
                break;
        default:
                shellbuf[cursorpos] = c;
                ++cursorpos;
                break;
        }
}

static bool listening = false;
static bool caps = false;

static void on_key_press(enum keycode keycode)
{
        if (!listening)
                return;
        switch (keycode) {
        case KEYCODE_LEFT_SHIFT:
        case KEYCODE_RIGHT_SHIFT:
                caps = true;
                break;
        /* when enter is pressed, it suggests that the user wants the keyboard
         * to stop listening and process their current input
         */
        case KEYCODE_ENTER:
                put_char('\n');
                listening = false;
                break;
        default:;
                char c;
                if (caps)
                        c = any_to_upper(keycode_to_char(keycode));
                else
                        c = keycode_to_char(keycode);
                put_char(c);
                put_shell_buf_char(c);
                break;
        }
}

static void on_key_release(enum keycode keycode)
{
        if (!listening)
                return;
        switch (keycode) {
        case KEYCODE_LEFT_SHIFT:
        case KEYCODE_RIGHT_SHIFT:
                caps = false;
                break;
        }
}

void init_shell(void)
{
        add_ps2_key_press_callback(on_key_press);
        add_ps2_key_release_callback(on_key_release);
        log_info("initialized shell");
}

/* input will be read into shellbuf */
static void read_key_input(void)
{
        memset(shellbuf, '\0', SHELL_BUF_SIZE);
        cursorpos = 0;
        caps = false; /* caps might not be reset by default */
        listening = true;
        while (listening)
                continue;
}

void run_shell(void)
{
        bool running = true;
        while (running) {
                put_str("(efshell)> ");
                set_text_back_stop_pos(text_cursor_pos());
                read_key_input();
                if (strcmp(shellbuf, "help-me") == 0)
                        help_me_shell_cmd();
                else if (strcmp(shellbuf, "efkernel-version") == 0)
                        efkernel_version_shell_cmd();
                else if (strcmp(shellbuf, "efshell-version") == 0)
                        efshell_version_shell_cmd();
                else if (strcmp(shellbuf, "clear-screen") == 0)
                        clear_screen();
                else if (strcmp(shellbuf, "exit-shell") == 0)
                        running = false;
                else if (strcmp(shellbuf, "cause-panic") == 0)
                        panic("caused panic intentionally");
        }
        log_info("ran shell");
}

const char *shell_version(void)
{
        return VERSION(1, 0, 0);
}