#include "shell/defcmd.h"

#include "kernel.h"
#include "io/text.h"
#include "shell/shell.h"
#include "mem/layout.h"

void efkernel_version_shell_cmd(void)
{
        put_str("efkernel version ");
        put_str(kernel_version());
        put_char('\n');
}

void efshell_version_shell_cmd(void)
{
        put_str("efshell version ");
        put_str(shell_version());
        put_char('\n');
}

void help_me_shell_cmd(void)
{
        put_str("default efshell commands:\n"
                "\thelp-me: display this menu\n"
                "\tefkernel-version: display the efkernel version\n"
                "\tefshell-version: display the efshell version\n"
                "\tclear-screen: clear the screen of all text\n"
                "\texit-shell: stop execution of efshell\n"
                "\tcause-panic: cause a kernel panic intentionally\n"
                "\tmem-stats: displays statistics about memory\n");
}

void mem_stats_shell_cmd(void)
{
        print_mem_layout();
}