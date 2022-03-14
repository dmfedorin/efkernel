#ifndef PORT_H_RIlrgesZscv4C8kVk5OrSvvuQoQX8z5X
#define PORT_H_RIlrgesZscv4C8kVk5OrSvvuQoQX8z5X

#include <stdint.h>

enum port {
        PORT_PIC1_CTRL = 0x20,
        PORT_PIC1_DATA = 0x21,
        PORT_PS2_DATA = 0x60,
        PORT_PS2_CTRL = 0x64,
        PORT_PIC2_CTRL = 0xa0,
        PORT_PIC2_DATA = 0xa1,
        PORT_VGA_CTRL = 0x3d4,
        PORT_VGA_DATA = 0x3d5,
};

void write_port_byte(enum port p, uint8_t data);
uint8_t read_port_byte(enum port p);
void write_port_word(enum port p, uint16_t data);
uint16_t read_port_word(enum port p);
void write_port_long(enum port p, uint32_t data);
uint32_t read_port_long(enum port p);

/* io port operations are slow, it is wise to wait on them to finish */
void wait_port_io(void);

#endif