#include "mem/heap.h"

#include "mem/layout.h"
#include <stddef.h>
#include <stdbool.h>
#include "io/text.h"

struct heap_segment {
        struct heap_segment *prev, *next;
        int size;
};

static struct heap_segment *first_seg;

void init_heap(void)
{
        uint32_t first_lay_ent_base = free_mem_layout_entries()[0].base;
        first_seg = (struct heap_segment *)first_lay_ent_base;
        *first_seg = (struct heap_segment){
                .next = NULL,
                .prev = NULL,
                .size = 0,
        };
        log_info("initialized heap");
}

static bool is_region_free(const void *addr, int size)
{
        const struct heap_segment *seg;
        for (seg = first_seg; seg != NULL; seg = seg->next) {
                uint32_t seg_left = (uint32_t)seg;
                uint32_t region_left = (uint32_t)addr;
                uint32_t seg_right = (uint32_t)seg + sizeof(*seg) + seg->size;
                uint32_t region_right = (uint32_t)addr + size;
                if (region_right >= seg_left && region_left <= seg_right)
                        return false;
        }
        return true;
}

void *alloc_heap_mem(int size)
{
}

void dealloc_heap_mem(const void *addr)
{
}