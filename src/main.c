/* must be the first line of code for proper function */
__asm__("jmp main\n");

#include "kernel.h"
#include "shell/shell.h"
#include "mem/heap.h"
#include "io/text.h"

void main(void)
{
        init_kernel();
        init_shell();
        run_shell();
}