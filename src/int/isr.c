#include "int/isr.h"

#include "kernel.h"
#include "io/text.h"
#include <stdbool.h>
#include "int/pic.h"
#include "io/port.h"
#include "io/ps2kb.h"

__attribute__((interrupt)) void default_isr(const struct int_frame *frame)
{
}

__attribute__((interrupt)) void div_by_0_isr(const struct int_frame *frame)
{
        /* remove panic later, this is obviously a recoverable error */
        panic("division by 0");
}

__attribute__((interrupt)) void debug_isr(const struct int_frame *frame)
{
        log_info("debug isr called");
}

__attribute__((interrupt)) void keyboard_isr(const struct int_frame *frame)
{
        uint8_t scancode = read_port_byte(PORT_PS2_DATA);
        
        ps2_key_event(scancode);
        
        end_pic1_int();
}