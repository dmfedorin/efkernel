#include "kernel.h"

#include "io/text.h"
#include <stdbool.h>

void panic(const char *msg)
{
        put_str("\r\x4f");

        clear_screen();

        put_str("kernel panic! an unrecoverable error was encountered\n");
        put_str(msg);

        while (true);
}