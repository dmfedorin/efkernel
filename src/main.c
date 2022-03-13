#include "io/text.h"
#include "int/idt.h"

void main(void)
{
        clear_screen();

        put_str("<<<hello world\n"
                "and newline...new\n"
                "line\n"
                "\n"
                "\r\x1f" "AND COLOR!!!!!");
}