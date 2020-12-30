#ifndef PIC_H
#define PIC_H

#include <stdint.h>

//https://wiki.osdev.org/PIC

typedef enum _PIC_PORTS{
    PIC1_COMMAND = 0x20,
    PIC1_DATA = 0x21,
    PIC2_COMMAND = 0xA0,
    PIC2_DATA = 0xA1
} PIC_PORTS;

typedef enum _PIC_COMMANDS{
    PIC_END = 0x20,
    PIC_INIT = 0x11,
    PIC_MODE_8086 = 0x01,
    PIC1_DISABLE = 0xFD,
    PIC2_DISABLE = 0xFF
} PIC_COMMANDS;

void PIC_Init(uint8_t offset1, uint8_t offset2);
void PIC_ClearInt(void);
void PIC_Disable(void);
void PIC_SetMask(uint8_t irq, uint8_t value);

#endif //PIC_H