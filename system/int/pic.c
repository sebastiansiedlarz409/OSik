#include "pic.h"
#include "../hal/hal.h"

#include <stdint.h>

//https://wiki.osdev.org/PIC

void PIC_Init(uint8_t offset1, uint8_t offset2)
{
    //save mask
    uint8_t mask1 = 0;
    uint8_t mask2 = 0;
    HAL_PortInByte(PIC1_DATA, &mask1);
    HAL_PortInByte(PIC2_DATA, &mask2);

    //init
    HAL_PortOutByte(PIC1_COMMAND, PIC_INIT);
    HAL_PortOutByte(PIC2_COMMAND, PIC_INIT);

    //set offsets
    HAL_PortOutByte(PIC1_DATA, offset1);
    HAL_PortOutByte(PIC2_DATA, offset2);

    //tell master about slave at irq2
    HAL_PortOutByte(PIC1_DATA, 4);

    //tell slave about cascade mode
    HAL_PortOutByte(PIC2_DATA, 2);

    //send mode
    HAL_PortOutByte(PIC1_DATA, PIC_MODE_8086);
    HAL_PortOutByte(PIC2_DATA, PIC_MODE_8086);

    //restore mask
    HAL_PortOutByte(PIC1_DATA, mask1);
    HAL_PortOutByte(PIC2_DATA, mask2);
}

void PIC_ClearInt(void)
{
    HAL_PortOutByte(PIC1_COMMAND, PIC_END);
    HAL_PortOutByte(PIC2_COMMAND, PIC_END);
}

void PIC_Disable(void)
{
    //disable pic for apic
    HAL_PortOutByte(PIC1_DATA, PIC1_DISABLE);
    HAL_PortOutByte(PIC2_DATA, PIC2_DISABLE);
}

void PIC_SetMask(uint8_t irq, uint8_t value)
{
    //save mask
    uint8_t mask1 = 0;
    uint8_t mask2 = 0;
    HAL_PortInByte(PIC1_DATA, &mask1);
    HAL_PortInByte(PIC2_DATA, &mask2);

    if (irq < 8){
        HAL_PortOutByte(PIC1_DATA, mask1 | (value << irq));
    }
    else{
        irq-=8;
        HAL_PortOutByte(PIC1_DATA, mask1 | (value << irq));
    }
}