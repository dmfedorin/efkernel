#include "mem/layout.h"

#include <stdint.h>
#include "io/text.h"

/* efboot loads detected memory layout to 0x500 */
#define MEM_LAYOUT_PTR ((const struct layout_entry *)0x500)

struct layout_entry {
        uint64_t base, size;
        uint32_t type, acpiextattr;
};

enum layout_entry_type {
        LAYOUT_ENTRY_TYPE_NULL = 0,
        LAYOUT_ENTRY_TYPE_FREE = 1,
        LAYOUT_ENTRY_TYPE_RESERVED = 2,
        LAYOUT_ENTRY_TYPE_ACPI_RECLAIMABLE = 3,
        LAYOUT_ENTRY_TYPE_ACPI_NVS = 4,
        LAYOUT_ENTRY_TYPE_BAD = 5,
};

void print_mem_layout(void)
{
        put_str("base               size               type\n");
        const struct layout_entry *layent = MEM_LAYOUT_PTR;
        while (layent->type != LAYOUT_ENTRY_TYPE_NULL) {
                put_hex_64(layent->base);
                put_char(' ');
                put_hex_64(layent->size);
                put_char(' ');
                put_hex(layent->type);
                put_char('\n');
                ++layent;
        }
}