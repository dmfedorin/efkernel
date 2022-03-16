#include "kernel.h"

#include "io/text.h"
#include <stdbool.h>
#include <stddef.h>

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