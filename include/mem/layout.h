#ifndef LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv
#define LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv

#include <stdbool.h>
#include <stdint.h>

void print_mem_layout(void);
bool is_free_in_mem_layout(const void *ptr, int size);
void init_mem_layout(void);

struct mem_layout_entry {
        uint64_t base, size;
        uint32_t type, acpi_ext_attr;
};

const struct mem_layout_entry *free_mem_layout_entries(void);
bool mem_regions_collide(const void *base_0, int size_0, const void *base_1,
                         int size_1);

#endif