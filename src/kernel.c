#include "kernel.h"

#include "io/text.h"
#include <stdbool.h>
#include <stddef.h>
#include "int/idt.h"
#include "int/pic.h"
#include "io/ps2kb.h"

struct cpu_regs get_cpu_regs(void)
{
        struct cpu_regs regs;
        __asm__("mov %%eax, %0\n"
                "mov %%ebx, %1\n"
                "mov %%ecx, %2\n"
                "mov %%edx, %3\n"
                "mov %%esp, %4\n"
                "mov %%ebp, %5\n"
                "mov %%esi, %6\n"
                "mov %%edi, %7\n"
                : "=m" (regs.eax), "=m" (regs.ebx), "=m" (regs.ecx),
                  "=m" (regs.edx), "=m" (regs.esp), "=m" (regs.ebp),
                  "=m" (regs.esi), "=m" (regs.edi));
        return regs;
}

void panic(const char *msg)
{
        clear_screen();
        put_str("kernel panic! an unrecoverable error was encountered\n");
        put_str(msg);
        while (true);
}

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
        mask_pic_ints(~(1 << 1), 0);
        __asm__("sti\n");
        log_info("initialized interrupts");
}

void init_kernel(void)
{
        init_ints();
        init_ps2_keyboard(KEYBOARD_LAYOUT_COLEMAK);
}