#include "io/port.h"

void write_port_byte(enum port p, uint8_t data)
{
        __asm__("outb %0, %1\n"
                :
                : "a" (data), "Nd" (p));
}

uint8_t read_port_byte(enum port p)
{
        uint8_t res;
        __asm__("inb %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        return res;
}

void write_port_word(enum port p, uint16_t data)
{
        __asm__("outw %0, %1\n"
                :
                : "a" (data), "Nd" (p));
}

uint16_t read_port_word(enum port p)
{
        uint16_t res;
        __asm__("inw %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        return res;
}

void write_port_long(enum port p, uint32_t data)
{
        __asm__("outl %0, %1\n"
                :
                : "a" (data), "Nd" (p));
}

uint32_t read_port_long(enum port p)
{
        uint32_t res;
        __asm__("inl %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        return res;
}

/* io port operations are slow, it is wise to wait on them to finish */
void wait_port_io(void)
{
        __asm__("outl %0, $0x80\n"
                :
                : "a" (0));
}