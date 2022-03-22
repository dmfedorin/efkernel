#include "mem/paging.h"

#include <stdint.h>
#include "io/text.h"

struct page_dir_entry {
        uint32_t present : 1, writeperm : 1, useraccess : 1, writethrough : 1,
                 cachedisabled : 1, accessed : 1, available0 : 1,
                 pagesize : 1, available1 : 4, addr : 20;
};