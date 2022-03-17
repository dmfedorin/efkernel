#include "libc/string.h"

#include <stdbool.h>

void memset(void *dst, uint8_t b, int size)
{
        for (int i = 0; i < size; ++i)
                *(uint8_t *)((uintptr_t)dst + i) = b;
}

void memcpy(void *restrict dst, const void *restrict src, int size)
{
        for (int i = 0; i < size; ++i) {
                *(uint8_t *)((uintptr_t)dst + i)
                        = *(uint8_t *)((uintptr_t)src + i);
        }
}

void strcpy(char *restrict dst, const char *restrict src)
{
        int i;
        for (i = 0; src[i] != '\0'; ++i)
                dst[i] = src[i];
        dst[i + 1] = '\0'; /* add null terminator */
}

void strncpy(char *restrict dst, const char *restrict src, int size)
{
        int i;
        for (i = 0; src[i] != '\0' && i < size; ++i)
                dst[i] = src[i];
        dst[i + 1] = '\0'; /* add null terminator */
}

void strcat(char *dst, const char *restrict src)
{
        char *restrict dstend = dst;
        while (*dstend != '\0')
                ++dstend;
        strcpy(dstend, src);
}

void strncat(char *dst, const char *restrict src, int size)
{
        char *restrict dstend = dst;
        while (*dstend != '\0')
                ++dstend;
        strncpy(dstend, src, size);
}