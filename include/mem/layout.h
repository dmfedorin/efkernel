#ifndef LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv
#define LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv

#include <stdbool.h>
#include <stdint.h>

void print_mem_layout(void);
bool is_free_in_mem_layout(const void *addr, int size);
void init_mem_layout(void);

struct mem_layout_entry {
        uint64_t base, size;
        uint32_t type, acpi_ext_attr;
};

const struct mem_layout_entry *free_mem_layout_entries(void);

#endif