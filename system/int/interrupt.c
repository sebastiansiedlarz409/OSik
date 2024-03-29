#include "pic.h"
#include "../devices/pit.h"
#include "interrupt.h"
#include "interrupt_handlers.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

IDTE table[256];

extern void DefaultError_Wrapper(void);

extern void DivideError_Wrapper(void);
extern void PITInt_Wrapper(void);
extern void KeyboardInt_Wrapper(void);

uint16_t INT_SetIDTEntryFlags(uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p)
{
    return (uint16_t)(ist | (type << 8) | (dpl << 13) | (p << 15));
}

void INT_SetIDTEntry(IDTE* idte, uint64_t address, uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p)
{
    idte->offset_63_32 = (address >> 32);
    idte->offset_31_16 = ((address & 0xFFFF0000) >> 16);
    idte->offset_15_0 = (address & 0xFFFF);
    idte->flags = INT_SetIDTEntryFlags(ist, type, dpl, p);
    idte->seg_selector = 0x8;
}

void INT_SetIDTR(void)
{
    INT_SetIDTEntry(&table[0], (uint64_t)DivideError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[1], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[2], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[3], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[4], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[5], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[6], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[7], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    INT_SetIDTEntry(&table[8], (uint64_t)PITInt_Wrapper, 0, 0xE, 0, 1); //pit
    INT_SetIDTEntry(&table[9], (uint64_t)KeyboardInt_Wrapper, 0, 0xE, 0, 1); //keyboard
    for(int i = 10; i<256;i++){
        INT_SetIDTEntry(&table[i], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    }

    //INTEL 3A, page 200
    IDTP idtp = {
        256*16-1,
        (uint64_t)&table
    };

    //PIC_Init(0x8, 0x70); //default values

    __asm("lidt %0" : : "m"(idtp));
    __asm("sti");
}