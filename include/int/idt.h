#ifndef IDT_H_wkc5pzq3aorispuhj9hjc9410xk61kwe
#define IDT_H_wkc5pzq3aorispuhj9hjc9410xk61kwe

#include "isr.h"

void init_idt_default(void);
void load_idt(void);

enum idt_entry {
        IDT_ENTRY_DIV_BY_0 = 0,
};

void set_idt_entry_isr(enum idt_entry ent,
                       void (*isr)(const struct int_frame intframe));

#endif