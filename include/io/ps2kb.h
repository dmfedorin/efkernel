#ifndef PS2KB_H_58kqNZE1lPLHABnbSkX5nULKeZvzrV8u
#define PS2KB_H_58kqNZE1lPLHABnbSkX5nULKeZvzrV8u

#include <stdint.h>

enum keyboard_layout {
        KEYBOARD_LAYOUT_QWERTY,
        KEYBOARD_LAYOUT_COLEMAK,
};

void init_ps2_keyboard(enum keyboard_layout layout);
void ps2_key_event(uint8_t scancode);

#endif