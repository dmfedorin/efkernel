#include "io/ps2kb.h"

#include "io/text.h"
#include "libc/string.h"
#include <stdbool.h>

#define USED_SET_1_KEYS 89
#define MAX_EVENT_CALLBACKS 64

static enum keycode key_map[USED_SET_1_KEYS];

void init_ps2_keyboard(enum keyboard_layout layout)
{
        switch (layout) {
        case KEYBOARD_LAYOUT_QWERTY:
                /* implement later */
                break;
        case KEYBOARD_LAYOUT_COLEMAK:
        default:;
                enum keycode colemak_key_map[USED_SET_1_KEYS] = {
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
                        KEYCODE_F10, KEYCODE_NUM_LOCK, KEYCODE_SCROLL_LOCK,
                        KEYCODE_NUMPAD_7, KEYCODE_NUMPAD_8, KEYCODE_NUMPAD_9,
                        KEYCODE_NUMPAD_HYPHEN, KEYCODE_NUMPAD_4,
                        KEYCODE_NUMPAD_5, KEYCODE_NUMPAD_6,
                        KEYCODE_NUMPAD_PLUS, KEYCODE_NUMPAD_1,
                        KEYCODE_NUMPAD_2, KEYCODE_NUMPAD_3, KEYCODE_NUMPAD_0,
                        KEYCODE_NUMPAD_PERIOD, KEYCODE_NULL, KEYCODE_NULL,
                        KEYCODE_NULL, KEYCODE_F11, KEYCODE_F12,
                };
                memcpy(key_map, colemak_key_map, sizeof(key_map));
                break;
        }
        log_info("initialized ps2 keyboard");
}

static inline bool keycode_is_alpha(enum keycode keycode)
{
        return keycode >= KEYCODE_A && keycode <= KEYCODE_Z;
}

static inline bool keycode_is_num(enum keycode keycode)
{
        return keycode >= KEYCODE_0 && keycode <= KEYCODE_9;
}

static inline bool keycode_is_numpad_num(enum keycode keycode)
{
        return keycode >= KEYCODE_NUMPAD_0 && keycode <= KEYCODE_NUMPAD_9;
}

char keycode_to_char(enum keycode keycode)
{
        if (keycode_is_alpha(keycode))
                return 'a' + keycode - KEYCODE_A;
        else if (keycode_is_num(keycode))
                return '0' + keycode - KEYCODE_0;
        else if (keycode_is_numpad_num(keycode))
                return '0' + keycode - KEYCODE_NUMPAD_0;
        /* other keycodes arent as easy to handle and require dedicated cases
         */
        switch (keycode) {
        case KEYCODE_BACKSPACE:
                return '\b';
        case KEYCODE_TAB:
                return '\t';
        case KEYCODE_ENTER:
                return '\n';
        case KEYCODE_SPACE:
                return ' ';
        case KEYCODE_HYPHEN:
        case KEYCODE_NUMPAD_HYPHEN:
                return '-';
        case KEYCODE_EQUALS:
                return '=';
        case KEYCODE_SEMICOLON:
                return ';';
        case KEYCODE_LEFT_BRACKET:
                return '[';
        case KEYCODE_RIGHT_BRACKET:
                return ']';
        case KEYCODE_QUOTE:
                return '\'';
        case KEYCODE_BACKTICK:
                return '`';
        case KEYCODE_BACKSLASH:
                return '\\';
        case KEYCODE_COMMA:
                return ',';
        case KEYCODE_PERIOD:
        case KEYCODE_NUMPAD_PERIOD:
                return '.';
        case KEYCODE_NUMPAD_ASTERISK:
                return '*';
        case KEYCODE_NUMPAD_PLUS:
                return '+';
        default:
                return '\0';
        }
}

static void (*press_callbacks[MAX_EVENT_CALLBACKS])(enum keycode keycode);
static int next_press_callback = 0;

static void (*release_callbacks[MAX_EVENT_CALLBACKS])(enum keycode keycode);
static int next_release_callback = 0;

static inline bool is_press(uint8_t scancode)
{
        return scancode < USED_SET_1_KEYS;
}

static inline bool is_release(uint8_t scancode)
{
        return scancode >= 0x81 && scancode <= 0x81 + USED_SET_1_KEYS;
}

void ps2_key_event(uint8_t scancode)
{
        if (is_press(scancode)) {
                for (int i = 0; i < next_press_callback; ++i)
                        press_callbacks[i](key_map[scancode]);
        } else if (is_release(scancode)) {
                for (int i = 0; i < next_release_callback; ++i)
                        release_callbacks[i](key_map[scancode - 0x80]);
        }
}

void add_ps2_key_press_callback(void (*callback)(enum keycode keycode))
{
        press_callbacks[next_press_callback] = callback;
        ++next_press_callback;
}

void add_ps2_key_release_callback(void (*callback)(enum keycode keycode))
{
        release_callbacks[next_release_callback] = callback;
        ++next_release_callback;
}