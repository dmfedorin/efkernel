#include "mem/layout.h"

#include <stdint.h>

/* efboot loads detected memory layout to 0x500 */
#define MEM_LAYOUT_PTR ((struct mem_layout_entry *)0x500)

struct mem_layout_entry {
        uint64_t base, size;
        uint32_t type, acpiextattr;
};