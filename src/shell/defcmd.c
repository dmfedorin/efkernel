#include "shell/defcmd.h"

#include "kernel.h"
#include "io/text.h"

void efk_version_cmd(void)
{
        put_str("efkernel version ");
        put_str(kernel_version());
        put_char('\n');
}