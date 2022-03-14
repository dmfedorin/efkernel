#ifndef DEFS_H_5Sd217saxjGcbXsJ07rG13nj25TqHATK
#define DEFS_H_5Sd217saxjGcbXsJ07rG13nj25TqHATK

#define KERNEL_CODE_SEG 0x8
#define KERNEL_DATA_SEG 0x10
#define OFFSET_LOW(ptr) ((uint16_t)((uint32_t)ptr & 0xffff))
#define OFFSET_HIGH(ptr) ((uint16_t)(((uint32_t)ptr & 0xffff0000) >> 16))

#endif