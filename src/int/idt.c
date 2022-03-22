#include "int/idt.h"

#include "int/isr.h"
#include "defs.h"
#include <stdalign.h>
#include "io/text.h"

#define IDT_SIZE 256

struct int_desc {
        uint16_t offsetlow, selector;
        uint8_t _zero, typeattr;
        uint16_t offsethigh;
} __attribute__((packed));

static struct int_desc idt[IDT_SIZE];

void init_idt_default(void)
{
        for (int i = 0; i < IDT_SIZE; ++i) {
                idt[i] = (struct int_desc){
                        .offsethigh = OFFSET_HIGH(default_isr),
                        .offsetlow = OFFSET_LOW(default_isr),
                        .selector = KERNEL_CODE_SEG,
                        .typeattr = INT_DESC_GATE_TYPE_INT,
                        ._zero = 0,
                };
        }
        log_info("initialized idt with default isr");
}

struct idtr {
        uint16_t size;
        uint32_t offset;
} __attribute__((packed));

void load_idt(void)
{
        struct idtr idtr = {
                .offset = (uint32_t)idt,
                .size = sizeof(idt) - 1,
        };
        __asm__("lidt %0\n"
                :
                : "m" (idtr));
        log_info("loaded idt");
}

void set_idt_entry_isr(enum idt_entry ent, enum int_desc_gate_type gatetype,
                       void (*isr)(const struct int_frame *frame))
{
        idt[ent].offsethigh = OFFSET_HIGH(isr);
        idt[ent].offsetlow = OFFSET_LOW(isr);
        idt[ent].typeattr = (uint8_t)gatetype;
}