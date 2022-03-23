#include "mem/layout.h"

#include <stdint.h>
#include "io/text.h"

/* efboot loads detected memory layout to 0x500 */
#define MEM_LAYOUT_PTR ((struct layout_entry *)0x500)

#define MAX_FREE_LAYOUT_ENTRIES 64
#define MAX_ADDRESSABLE_LAYOUT_ENTRY_BASE 0xffffffff
#define MAX_KERNEL_RESERVED_ADDR 0xfffff

struct layout_entry {
        uint64_t base, size;
        uint32_t type, acpiextattr;
};

enum layout_entry_type {
        LAYOUT_ENTRY_TYPE_NULL = 0,
        LAYOUT_ENTRY_TYPE_FREE = 1,
        LAYOUT_ENTRY_TYPE_RESERVED = 2,
        LAYOUT_ENTRY_TYPE_RECLAIMABLE = 3,
        LAYOUT_ENTRY_TYPE_NON_VOLATILE = 4,
        LAYOUT_ENTRY_TYPE_BAD = 5,
        LAYOUT_ENTRY_TYPE_KERNEL_RESERVED = 6, /* some entries are rendered
                                                * unusable because of their
                                                * usage in the kernel, and
                                                * will be marked as such on
                                                * init_mem_layout()
                                                */
};

/* this invalidates layout entries which cannot be addressed */
static inline bool is_valid_layout_entry(const struct layout_entry *layent)
{
        return layent->base <= MAX_ADDRESSABLE_LAYOUT_ENTRY_BASE
               && layent->type != LAYOUT_ENTRY_TYPE_NULL;
}

void print_mem_layout(void)
{
        put_str("base       size       type       type decoded\n");
        const char *typedecodemap[] = {
                "null", "free", "reserved", "reclaimable", "non-volatile",
                "bad", "kernel-reserved",
        };
        const struct layout_entry *layent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(layent)) {
                put_hex(layent->base);
                put_char(' ');
                put_hex(layent->size);
                put_char(' ');
                put_hex(layent->type);
                put_char(' ');
                put_str(typedecodemap[layent->type]);
                put_char('\n');
                ++layent;
        }
}

static struct layout_entry freelayents[MAX_FREE_LAYOUT_ENTRIES] = { 0 };
static int nextfreelayent = 0;

bool is_free_in_mem_layout(const void *addr, int size)
{
        for (int i = 0; i < nextfreelayent; ++i) {
                uint32_t entend = freelayents[i].base + freelayents[i].size;
                bool free = (uint32_t)addr >= freelayents[i].base
                            && (uint32_t)addr + size <= entend;
                if (free)
                        return true;
        }
        return false;
}

static void mark_kernel_reserved_layout_entries(void)
{
        struct layout_entry *layent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(layent)) {
                if (layent->base + layent->size <= MAX_KERNEL_RESERVED_ADDR)
                        layent->type = LAYOUT_ENTRY_TYPE_KERNEL_RESERVED;
                ++layent;
        }
}

static void save_free_layout_entries(void)
{
        const struct layout_entry *layent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(layent)) {
                if (layent->type == LAYOUT_ENTRY_TYPE_FREE) {
                        freelayents[nextfreelayent] = *layent;
                        ++nextfreelayent;
                }
                ++layent;
        }
}

void init_mem_layout(void)
{
        mark_kernel_reserved_layout_entries();
        save_free_layout_entries();
        log_info("initialized memory layout");
}