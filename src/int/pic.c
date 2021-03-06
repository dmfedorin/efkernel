#include "int/pic.h"

#include "io/text.h"
#include "io/port.h"
#include <stdint.h>

#define END_OF_INT 0x20

enum init_ctrl_word {
        INIT_CTRL_WORD_1_ICW4 = 0x1,
        INIT_CTRL_WORD_4_8086 = 0x1,
        INIT_CTRL_WORD_1_INIT = 0x10,
};

void remap_pic(void)
{
        uint8_t int_mask_1 = read_port_byte(PORT_PIC1_DATA);
        wait_port_io();
        uint8_t int_mask_2 = read_port_byte(PORT_PIC2_DATA);
        wait_port_io();
        write_port_byte(PORT_PIC1_CTRL,
                        INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_ICW4);
        wait_port_io();
        write_port_byte(PORT_PIC2_CTRL,
                        INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_ICW4);
        wait_port_io();
        /* best not collide with an existing interrupt like an exception,
         * remap pic to avoid since the last exception interrupt is 0x1f
         */
        write_port_byte(PORT_PIC1_DATA, 0x20);
        wait_port_io();
        write_port_byte(PORT_PIC2_DATA, 0x28);
        wait_port_io();
        write_port_byte(PORT_PIC1_DATA, 4);
        wait_port_io();
        write_port_byte(PORT_PIC2_DATA, 2);
        wait_port_io();
        write_port_byte(PORT_PIC1_DATA, INIT_CTRL_WORD_4_8086);
        wait_port_io();
        write_port_byte(PORT_PIC2_DATA, INIT_CTRL_WORD_4_8086);
        wait_port_io();
        mask_pic_ints(int_mask_1, int_mask_2);
        log_info("remapped pic");
}

void mask_pic_ints(uint8_t int_mask_1, uint8_t int_mask_2)
{
        write_port_byte(PORT_PIC1_DATA, int_mask_1);
        wait_port_io();
        write_port_byte(PORT_PIC2_DATA, int_mask_2);
        wait_port_io();
}

void end_pic1_int(void)
{
        write_port_byte(PORT_PIC1_CTRL, END_OF_INT);
        wait_port_io();
}

void end_pic2_int(void)
{
        write_port_byte(PORT_PIC2_CTRL, END_OF_INT);
        wait_port_io();
        write_port_byte(PORT_PIC1_CTRL, END_OF_INT);
        wait_port_io();
}