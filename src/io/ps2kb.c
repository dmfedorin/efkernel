#include "io/ps2kb.h"

#include "io/text.h"
#include "libc/string.h"

#define USED_SET_1_KEYS 89

enum keycode {
        KEYCODE_NULL,

        KEYCODE_A,
        KEYCODE_B,
        KEYCODE_C,
        KEYCODE_D,
        KEYCODE_E,
        KEYCODE_F,
        KEYCODE_G,
        KEYCODE_H,
        KEYCODE_I,
        KEYCODE_J,
        KEYCODE_K,
        KEYCODE_L,
        KEYCODE_M,
        KEYCODE_N,
        KEYCODE_O,
        KEYCODE_P,
        KEYCODE_Q,
        KEYCODE_R,
        KEYCODE_S,
        KEYCODE_T,
        KEYCODE_U,
        KEYCODE_V,
        KEYCODE_W,
        KEYCODE_X,
        KEYCODE_Y,
        KEYCODE_Z,

        KEYCODE_0,
        KEYCODE_1,
        KEYCODE_2,
        KEYCODE_3,
        KEYCODE_4,
        KEYCODE_5,
        KEYCODE_6,
        KEYCODE_7,
        KEYCODE_8,
        KEYCODE_9,

        KEYCODE_ESC,
        KEYCODE_BACKSPACE,
        KEYCODE_TAB,
        KEYCODE_ENTER,
        KEYCODE_LEFT_CTRL,
        KEYCODE_LEFT_SHIFT,
        KEYCODE_RIGHT_SHIFT,
        KEYCODE_LEFT_ALT,
        KEYCODE_SPACE,
        KEYCODE_CAPS_LOCK,

        KEYCODE_HYPHEN,
        KEYCODE_EQUALS,
        KEYCODE_SEMICOLON,
        KEYCODE_LEFT_BRACKET,
        KEYCODE_RIGHT_BRACKET,
        KEYCODE_QUOTE,
        KEYCODE_BACKTICK,
        KEYCODE_BACKSLASH,
        KEYCODE_COMMA,
        KEYCODE_PERIOD,
        KEYCODE_SLASH,

        KEYCODE_NUMPAD_ASTERISK,

        KEYCODE_F1,
        KEYCODE_F2,
        KEYCODE_F3,
        KEYCODE_F4,
        KEYCODE_F5,
        KEYCODE_F6,
        KEYCODE_F7,
        KEYCODE_F8,
        KEYCODE_F9,
        KEYCODE_F10,
        KEYCODE_F11,
        KEYCODE_F12,
};

static enum keycode keymap[USED_SET_1_KEYS];

void init_ps2_keyboard(enum keyboard_layout layout)
{
        switch (layout) {
        case KEYBOARD_LAYOUT_QWERTY:
                /* implement later */
                break;
        case KEYBOARD_LAYOUT_COLEMAK:
        default:
                enum keycode colemakkeymap[USED_SET_1_KEYS] = {
                        KEYCODE_NULL, KEYCODE_ESC, KEYCODE_1, KEYCODE_2,
                        KEYCODE_3, KEYCODE_4, KEYCODE_5, KEYCODE_6, KEYCODE_7,
                        KEYCODE_8, KEYCODE_9, KEYCODE_0, KEYCODE_HYPHEN,
                        KEYCODE_EQUALS, KEYCODE_BACKSPACE, KEYCODE_TAB,
                        KEYCODE_Q, KEYCODE_W, KEYCODE_F, KEYCODE_P, KEYCODE_G,
                        KEYCODE_J, KEYCODE_L, KEYCODE_U, KEYCODE_Y,
                        KEYCODE_SEMICOLON, KEYCODE_LEFT_BRACKET,
                        KEYCODE_RIGHT_BRACKET, KEYCODE_ENTER,
                        KEYCODE_LEFT_CTRL, KEYCODE_A, KEYCODE_R, KEYCODE_S,
                        KEYCODE_T, KEYCODE_D, KEYCODE_H, KEYCODE_N, KEYCODE_E,
                        KEYCODE_I, KEYCODE_O, KEYCODE_QUOTE, KEYCODE_BACKTICK,
                        KEYCODE_LEFT_SHIFT, KEYCODE_BACKSLASH, KEYCODE_Z,
                        KEYCODE_X, KEYCODE_C, KEYCODE_V, KEYCODE_B, KEYCODE_K,
                        KEYCODE_M, KEYCODE_COMMA, KEYCODE_PERIOD,
                        KEYCODE_SLASH, KEYCODE_RIGHT_SHIFT,
                        KEYCODE_NUMPAD_ASTERISK, KEYCODE_LEFT_ALT,
                        KEYCODE_SPACE, KEYCODE_CAPS_LOCK, KEYCODE_F1,
                        KEYCODE_F2, KEYCODE_F3, KEYCODE_F4, KEYCODE_F5,
                        KEYCODE_F6, KEYCODE_F7, KEYCODE_F8, KEYCODE_F9,
                        KEYCODE_F10, /* finish later */
                };

                memcpy(keymap, colemakkeymap, sizeof(keymap));

                break;
        }
}

void ps2_key_event(uint8_t scancode)
{
        if (scancode > USED_SET_1_KEYS - 1)
                return;

        put_hex(scancode);
}