#include "int/idt.h"

#include "int/isr.h"

#define IDT_SIZE 256

struct int_desc {
        uint16_t offsetlow, selector;
        uint8_t _zero, typeattr;
        uint16_t offsethigh;
};

static struct int_desc idt[IDT_SIZE];

void init_idt_default(void)
{
        for (int i = 0; i < IDT_SIZE; ++i) {
                idt[i] = (struct int_desc){
                };
        }
}

void load_idt(void)
{
}