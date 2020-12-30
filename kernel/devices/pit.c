#include "pit.h"
#include "../hal/hal.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

//https://wiki.osdev.org/Programmable_Interval_Timer
uint16_t divisor = 1193;

uint64_t PIT_CH0_COUNTER;

uint8_t PIT_SetConfig(uint8_t channel, uint8_t accessMode, uint8_t mode, uint8_t bcd)
{
    return (channel << 6) | (accessMode << 4) | (mode << 1) | bcd;
}

void PIT_Init(void)
{
    //HAL_PortOutByte(PIT_COMMAND, PIT_SetConfig(PIT_CH0_CHANNELS, PIT_AC_HLB, PIT_M0, PIT_BIN));
    HAL_PortOutByte(PIT_COMMAND, 0b00110100);
    HAL_PortOutByte(PIT_CH0_COMMAND, divisor & 0xFF); //low
    HAL_PortOutByte(PIT_CH0_COMMAND, (divisor >> 8) & 0xFF); //high
}

void PIT_Reload(void)
{
    HAL_PortOutByte(PIT_CH0_COMMAND, divisor & 0xFF); //low
    HAL_PortOutByte(PIT_CH0_COMMAND, (divisor >> 8) & 0xFF); //high
}

void PIT_Count(void)
{
    if(PIT_CH0_COUNTER < UINT64_MAX)
        PIT_CH0_COUNTER++;

    print(Terminal_B8000_8025_GetTerminalContext(), "%x \r\n", PIT_CH0_COUNTER);
}