/* must be the first line of code for proper function*/
__asm__("jmp main\n");

#include "io/text.h"
#include "int/idt.h"
#include "int/pic.h"
#include "io/ps2kb.h"
#include "mem/layout.h"

static void init_ints(void)
{
        init_idt_default();
        set_idt_entry_isr(IDT_ENTRY_DIV_BY_0, INT_DESC_GATE_TYPE_TRAP,
                          div_by_0_isr);
        set_idt_entry_isr(IDT_ENTRY_DEBUG, INT_DESC_GATE_TYPE_INT, debug_isr);
        set_idt_entry_isr(IDT_ENTRY_KEYBOARD, INT_DESC_GATE_TYPE_INT,
                          keyboard_isr);
        load_idt();
        remap_pic();
        mask_pic_ints(0b11111101, 0b11111111);
        __asm__("sti\n");
        log_info("initialized interrupts");
}

void main(void)
{
        clear_screen();
        init_ints();
        init_ps2_keyboard(KEYBOARD_LAYOUT_COLEMAK);
        print_mem_layout();
}