#ifndef STRING_H_FbgAexDJrajIMnIaGVyvAX4PXREPJOQp
#define STRING_H_FbgAexDJrajIMnIaGVyvAX4PXREPJOQp

#include <stdint.h>

void memset(void *dst, uint8_t b, int size);
void memcpy(void *restrict dst, const void *restrict src, int size);
void strcpy(char *restrict dst, const char *restrict src);
void strncpy(char *restrict dst, const char *restrict src, int size);
void strcat(char *dst, const char *restrict src);
void strncat(char *dst, const char *restrict src, int size);

#endif