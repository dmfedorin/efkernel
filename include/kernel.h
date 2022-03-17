#ifndef KERNEL_H_UEx8tCf4ZWS5dFGUtKBp4gV3iFYNPmpI
#define KERNEL_H_UEx8tCf4ZWS5dFGUtKBp4gV3iFYNPmpI

#include <stdint.h>

struct cpu_regs {
        uint32_t eax, ebx, ecx, edx, esp, ebp, esi, edi;
};

struct cpu_regs get_cpu_regs(void);
void panic(const char *msg);
void init_kernel(void);

#endif