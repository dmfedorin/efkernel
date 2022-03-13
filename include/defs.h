#ifndef DEFS_H_6gx8vocbk5znrq3ty9tce03zg4af8hze
#define DEFS_H_6gx8vocbk5znrq3ty9tce03zg4af8hze

#define KERNEL_CODE_SEG 0x8
#define KERNEL_DATA_SEG 0x10
#define OFFSET_LOW(ptr) ((uint16_t)((uint32_t)ptr & 0xffff))
#define OFFSET_HIGH(ptr) ((uint16_t)(((uint32_t)ptr & 0xffff0000) >> 16))

#endif