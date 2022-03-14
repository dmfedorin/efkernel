#include "int/isr.h"

#include "io/text.h"
#include <stdbool.h>

__attribute__((interrupt)) void default_isr(const struct int_frame *frame)
{
}

__attribute__((interrupt)) void div_by_0_isr(const struct int_frame *frame)
{
        log_info("division by 0");

        while (true);
}