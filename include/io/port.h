#ifndef PORT_H_164yx07uk0l05crjnlx76foja9ttpcjq
#define PORT_H_164yx07uk0l05crjnlx76foja9ttpcjq

#include <stdint.h>

enum port {
        PORT_VGA_CTRL = 0x3d4,
        PORT_VGA_DATA = 0x3d5,
};

void write_port_byte(enum port p, uint8_t data);
uint8_t read_port_byte(enum port p);
void write_port_word(enum port p, uint16_t data);
uint16_t read_port_word(enum port p);
void write_port_long(enum port p, uint32_t data);
uint32_t read_port_long(enum port p);

// io port operations are slow, it is wise to wait on them to finish
void wait_port(enum port p);

#endif