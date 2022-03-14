#ifndef ISR_H_hpoyDRx4106B9qwttkUjQpLELCCUbFRr
#define ISR_H_hpoyDRx4106B9qwttkUjQpLELCCUbFRr

#include <stdint.h>

struct int_frame {
        uint16_t ip, cs, flags, sp, ss;
};

__attribute__((interrupt)) void default_isr(const struct int_frame *frame);
__attribute__((interrupt)) void div_by_0_isr(const struct int_frame *frame);
__attribute__((interrupt)) void debug_isr(const struct int_frame *frame);
__attribute__((interrupt)) void keyboard_isr(const struct int_frame *frame);

#endif