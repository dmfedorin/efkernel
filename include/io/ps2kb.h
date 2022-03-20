#ifndef PS2KB_H_58kqNZE1lPLHABnbSkX5nULKeZvzrV8u
#define PS2KB_H_58kqNZE1lPLHABnbSkX5nULKeZvzrV8u

#include <stdint.h>

enum keyboard_layout {
        KEYBOARD_LAYOUT_QWERTY,
        KEYBOARD_LAYOUT_COLEMAK,
};

void init_ps2_keyboard(enum keyboard_layout layout);
void ps2_key_event(uint8_t scancode);

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
        KEYCODE_NUM_LOCK,
        KEYCODE_SCROLL_LOCK,

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

        KEYCODE_NUMPAD_0,
        KEYCODE_NUMPAD_1,
        KEYCODE_NUMPAD_2,
        KEYCODE_NUMPAD_3,
        KEYCODE_NUMPAD_4,
        KEYCODE_NUMPAD_5,
        KEYCODE_NUMPAD_6,
        KEYCODE_NUMPAD_7,
        KEYCODE_NUMPAD_8,
        KEYCODE_NUMPAD_9,
        KEYCODE_NUMPAD_ASTERISK,
        KEYCODE_NUMPAD_HYPHEN,
        KEYCODE_NUMPAD_PLUS,
        KEYCODE_NUMPAD_PERIOD,

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

char keycode_to_char(enum keycode keycode);
void add_ps2_key_press_callback(void (*callback)(enum keycode keycode));
void add_ps2_key_release_callback(void (*callback)(enum keycode keycode));

#endif