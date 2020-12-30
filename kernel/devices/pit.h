#ifndef PIT_H
#define PIT_H

#include <stdint.h>

//FREQ = 1.1931816666 MHz

enum PIT_PORTS{
    PIT_COMMAND = 0x43,
    PIT_CH0_COMMAND = 0x40,
    PIT_CH1_COMMAND = 0x41,
    PIT_CH2_COMMAND = 0x42
};

enum PIT_CHANNELS{
    PIT_CH0_CHANNELS = 0x0,
    PIT_CH1_CHANNELS = 0x1,
    PIT_CH2_CHANNELS = 0x2,
    PIT_RB = 0x3
};

enum PIT_ACCESSMODES{
    PIT_AC_LATCH = 0x0,
    PIT_AC_LB = 0x1,
    PIT_AC_HB = 0x2,
    PIT_AC_HLB = 0x3
};

enum PIT_MODES{
    PIT_M0 = 0x0,           //(interrupt on terminal count)
    PIT_M1 = 0x1,           //(hardware re-triggerable one-shot)
    PIT_M2 = 0x2,           //(rate generator)
    PIT_M3 = 0x3,           //(square wave generator)
    PIT_M4 = 0x4,           //(software triggered strobe)
    PIT_M5 = 0x5,           //(hardware triggered strobe)
    PIT_M6 = 0x6,           //(rate generator, same as 010b)
    PIT_M7 = 0x7            //(square wave generator, same as 011b)
};

enum PIT_BCDMODE{
    PIT_BCD = 0x1,
    PIT_BIN = 0x0
};

void PIT_Init(void);
void PIT_Reload(void);
void PIT_Count(void);
void PIT_Sleep(uint64_t time);

#endif //PIT_H