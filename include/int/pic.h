#ifndef PIC_H_xXAluTrUpgHWAzqXpFinHd4m59CQ4NZz
#define PIC_H_xXAluTrUpgHWAzqXpFinHd4m59CQ4NZz

#include <stdint.h>

void remap_pic(void);
void mask_pic_ints(uint8_t intmask1, uint8_t intmask2);
void end_pic1_int(void);
void end_pic2_int(void);

#endif