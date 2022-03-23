#ifndef LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv
#define LAYOUT_H_AifX0Cwu6QbrN8iD3mduMAeCqyE6VpEv

#include <stdbool.h>

void print_mem_layout(void);
bool is_free_in_mem_layout(const void *addr, int size);
void init_mem_layout(void);

#endif