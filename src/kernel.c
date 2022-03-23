#include "kernel.h"

#include "io/text.h"
#include <stdbool.h>
#include <stddef.h>
#include "int/idt.h"
#include "int/pic.h"
#include "io/ps2kb.h"
#include "defs.h"
#include "mem/layout.h"

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

static void print_cpu_regs(const struct cpu_regs *regs)
{
        put_str("eax: ");
        put_hex(regs->eax);
        put_char('\n');
        put_str("ebx: ");
        put_hex(regs->ebx);
        put_char('\n');
        put_str("ecx: ");
        put_hex(regs->ecx);
        put_char('\n');
        put_str("edx: ");
        put_hex(regs->edx);
        put_char('\n');
        put_str("esp: ");
        put_hex(regs->esp);
        put_char('\n');
        put_str("ebp: ");
        put_hex(regs->ebp);
        put_char('\n');
        put_str("esi: ");
        put_hex(regs->esi);
        put_char('\n');
        put_str("edi: ");
        put_hex(regs->edi);
        put_char('\n');
}

void panic(const char *msg)
{
        struct cpu_regs regs = get_cpu_regs(); /* must be first to preserve
                                                * state of registers at call,
                                                * note that eax and ebx will
                                                * still probably be
                                                * overwritten
                                                */
        set_text_attr(TEXT_COLOR_WHITE, TEXT_COLOR_RED);
        clear_screen();
        put_str("kernel panic! an unrecoverable error was encountered\n"
                "error: ");
        put_str(msg);
        put_str("\n\n");
        print_cpu_regs(&regs);
        __asm__("cli\n");
        idle_until_int();
        while (true)
                continue;
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

static inline void init_io(void)
{
        init_ps2_keyboard(KEYBOARD_LAYOUT_COLEMAK);
        log_info("initialized io");
}

static inline void init_mem(void)
{
        init_mem_layout();
        log_info("initialized memory");
}

void init_kernel(void)
{
        init_ints();
        init_io();
        init_mem();
        log_info("initialized kernel");
}

void idle_until_int(void)
{
        __asm__("hlt\n");
}

const char *kernel_version(void)
{
        return VERSION(1, 0, 0);
}