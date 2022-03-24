#include "mem/heap.h"

#include "mem/layout.h"
#include <stddef.h>
#include <stdbool.h>
#include "io/text.h"
#include "libc/string.h"

struct segment_header {
        struct segment_header *prev, *next;
        int size;
};

static struct segment_header *first_seg, *last_seg;

void init_heap(void)
{
        uint32_t first_lay_ent_base = free_mem_layout_entries()[0].base;
        first_seg = (struct segment_header *)first_lay_ent_base;
        *first_seg = (struct segment_header){
                .next = NULL,
                .prev = NULL,
                .size = 0,
        };
        last_seg = first_seg;
        log_info("initialized heap");
}

static bool is_region_free(const void *ptr, int size)
{
        const struct segment_header *seg;
        for (seg = first_seg; seg != NULL; seg = seg->next) {
                bool occupied = mem_regions_collide(seg,
                                                    sizeof(*seg) + seg->size,
                                                    ptr, size);
                if (occupied)
                        return false;
        }
        return true;
}

static void *find_free_region(int size)
{
        const struct segment_header *seg;
        for (seg = first_seg; seg != NULL; seg = seg->next) {
                uintptr_t pot_free_addr = (uintptr_t)seg + sizeof(*seg)
                                          + seg->size + 1;
                if (is_region_free((const void *)pot_free_addr, size))
                        return (void *)pot_free_addr;
        }
        return NULL;
}

void *alloc_heap_mem(int size)
{
        int total_size = sizeof(struct segment_header) + size;
        void *alloc_region = find_free_region(total_size);
        if (alloc_region == NULL)
                return NULL;
        struct segment_header new_seg = {
                .next = NULL,
                .prev = last_seg,
                .size = size,
        };
        memcpy(alloc_region, &new_seg, sizeof(new_seg));
        last_seg->next = alloc_region;
        last_seg = alloc_region;
        void *seg_body = (void *)((uintptr_t)alloc_region + sizeof(new_seg));
        return seg_body;
}

static struct segment_header *find_header_of_allocation(const void *ptr)
{
        struct segment_header *seg;
        for (seg = first_seg; seg != NULL; seg = seg->next) {
                uintptr_t seg_base = (uintptr_t)seg + sizeof(*seg);
                bool correct_hdr = mem_regions_collide((const void *)seg_base,
                                                       seg->size, ptr, 0);
                if (correct_hdr)
                        return seg;
        }
        return NULL;
}

void dealloc_heap_mem(const void *ptr)
{
        struct segment_header *seg = find_header_of_allocation(ptr);
        if (seg == NULL)
                return;
        if (seg->prev != NULL)
                seg->prev->next = seg->next;
        if (seg->next != NULL)
                seg->next->prev = seg->prev;
}