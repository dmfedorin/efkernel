#include "int/idt.h"

#include "int/isr.h"
#include "defs.h"
#include "io/text.h"

#define IDT_SIZE 256

struct int_desc {
        uint16_t offset_low, selector;
        uint8_t _zero, type_attr;
        uint16_t offset_high;
} __attribute__((packed));

static struct int_desc idt[IDT_SIZE];

void init_idt_default(void)
{
        for (int i = 0; i < IDT_SIZE; ++i) {
                idt[i] = (struct int_desc){
                        .offset_high = OFFSET_HIGH(default_isr),
                        .offset_low = OFFSET_LOW(default_isr),
                        .selector = KERNEL_CODE_SEG,
                        .type_attr = INT_DESC_GATE_TYPE_INT,
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

void set_idt_entry_isr(enum idt_entry ent, enum int_desc_gate_type gate_type,
                       void (*isr)(const struct int_frame *frame))
{
        idt[ent].offset_high = OFFSET_HIGH(isr);
        idt[ent].offset_low = OFFSET_LOW(isr);
        idt[ent].type_attr = gate_type;
}