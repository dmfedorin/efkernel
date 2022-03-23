#include "mem/layout.h"

#include "io/text.h"

/* efboot loads detected memory layout to 0x500 */
#define MEM_LAYOUT_PTR ((struct mem_layout_entry *)0x500)

#define MAX_FREE_LAYOUT_ENTRIES 64
#define MAX_ADDRESSABLE_LAYOUT_ENTRY_BASE 0xffffffff
#define MAX_KERNEL_RESERVED_ADDR 0xfffff

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
static
inline bool is_valid_layout_entry(const struct mem_layout_entry *lay_ent)
{
        return lay_ent->base <= MAX_ADDRESSABLE_LAYOUT_ENTRY_BASE
               && lay_ent->type != LAYOUT_ENTRY_TYPE_NULL;
}

void print_mem_layout(void)
{
        put_str("base       size       type       type decoded\n");
        const char *type_decode_map[] = {
                "null", "free", "reserved", "reclaimable", "non-volatile",
                "bad", "kernel-reserved",
        };
        const struct mem_layout_entry *lay_ent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(lay_ent)) {
                put_hex(lay_ent->base);
                put_char(' ');
                put_hex(lay_ent->size);
                put_char(' ');
                put_hex(lay_ent->type);
                put_char(' ');
                put_str(type_decode_map[lay_ent->type]);
                put_char('\n');
                ++lay_ent;
        }
}

static struct mem_layout_entry free_lay_ents[MAX_FREE_LAYOUT_ENTRIES] = { 0 };
static int next_free_lay_ent = 0;

bool is_free_in_mem_layout(const void *addr, int size)
{
        for (int i = 0; i < next_free_lay_ent; ++i) {
                uint32_t ent_end = free_lay_ents[i].base
                                   + free_lay_ents[i].size;
                bool free = (uint32_t)addr >= free_lay_ents[i].base
                            && (uint32_t)addr + size <= ent_end;
                if (free)
                        return true;
        }
        return false;
}

static void mark_kernel_reserved_layout_entries(void)
{
        struct mem_layout_entry *lay_ent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(lay_ent)) {
                if (lay_ent->base + lay_ent->size <= MAX_KERNEL_RESERVED_ADDR)
                        lay_ent->type = LAYOUT_ENTRY_TYPE_KERNEL_RESERVED;
                ++lay_ent;
        }
}

static void save_free_layout_entries(void)
{
        const struct mem_layout_entry *lay_ent = MEM_LAYOUT_PTR;
        while (is_valid_layout_entry(lay_ent)) {
                if (lay_ent->type == LAYOUT_ENTRY_TYPE_FREE) {
                        free_lay_ents[next_free_lay_ent] = *lay_ent;
                        ++next_free_lay_ent;
                }
                ++lay_ent;
        }
}

void init_mem_layout(void)
{
        mark_kernel_reserved_layout_entries();
        save_free_layout_entries();
        log_info("initialized memory layout");
}

const struct mem_layout_entry *free_mem_layout_entries(void)
{
        return free_lay_ents;
}