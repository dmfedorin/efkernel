#ifndef ISR_H_k8zanpdxd5vlapjtfgs76w86tscbtppd
#define ISR_H_k8zanpdxd5vlapjtfgs76w86tscbtppd

#include <stdint.h>

struct int_frame {
        uint16_t ip, cs, flags, sp, ss;
};

__attribute__((interrupt)) void default_isr(const struct int_frame *frame);
__attribute__((interrupt)) void div_by_0_isr(const struct int_frame *frame);

#endif