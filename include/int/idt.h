#ifndef IDT_H_4gXG5sI6tOHCcb3DvVWjiFW3hyXrbNQe
#define IDT_H_4gXG5sI6tOHCcb3DvVWjiFW3hyXrbNQe

#include "isr.h"

void init_idt_default(void);
void load_idt(void);

enum idt_entry {
        IDT_ENTRY_DIV_BY_0 = 0x0,
        IDT_ENTRY_DEBUG = 0x1,
        IDT_ENTRY_KEYBOARD = 0x21, /* pic has to have been remapped */
};

enum int_desc_gate_type {
        INT_DESC_GATE_TYPE_TASK = 0x85,
        INT_DESC_GATE_TYPE_INT = 0x8e,
        INT_DESC_GATE_TYPE_TRAP = 0x8f,
};

void set_idt_entry_isr(enum idt_entry ent, enum int_desc_gate_type gate_type,
                       void (*isr)(const struct int_frame *frame));

#endif