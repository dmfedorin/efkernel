#ifndef CTYPE_H_8GHgeMNtYG19x622fQD8whKFSF3BtXKB
#define CTYPE_H_8GHgeMNtYG19x622fQD8whKFSF3BtXKB

#include <stdbool.h>

bool isalpha(char c);
bool isupper(char c);
bool islower(char c);
char toupper(char c);
char any_to_upper(char c); /* toupper but works for non alphabet characters */

#endif