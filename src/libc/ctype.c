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