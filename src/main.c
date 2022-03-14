#include "io/text.h"
#include "int/idt.h"

void main(void)
{
        clear_screen();

        init_idt_default();

        set_idt_entry_isr(IDT_ENTRY_DIV_BY_0, INT_DESC_GATE_TYPE_TRAP,
                          div_by_0_isr);

        load_idt();

        put_str("<<<hello world\n"
                "and newline...new\n"
                "line\n"
                "\n"
                "\r\x1f" "AND COLOR!!!!!");
}