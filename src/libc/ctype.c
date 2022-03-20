#include "libc/ctype.h"

bool isalpha(char c)
{
        return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool isupper(char c)
{
        return c >= 'A' && c <= 'Z';
}

bool islower(char c)
{
        return c >= 'a' && c <= 'z';
}

char toupper(char c)
{
        if (islower(c))
                return c - ('a' - 'A');
        else
                return c;
}

/* toupper but works for non alphabet characters */
char any_to_upper(char c)
{
        if (isalpha(c))
                return toupper(c);
        switch (c) {
        case '0': return ')';
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '`': return '~';
        case '-': return '_';
        case '=': return '+';
        case ';': return ':';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case '\'': return '"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        }
        return c;
}