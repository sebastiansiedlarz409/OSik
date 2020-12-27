#include "interrupt.h"
#include "interrupt_handlers.h"

#include <stdint.h>

//IDT SECTION

//INTERRUPT -> Intel 3A, page 199, chapter 6
//FOR LONG MODE -> Intel 3A, page 210m chapter 6.14
//Interrupt list -> Intel 3A, page 192

struct _IDTE {
  uint16_t offset_15_0;           //part of handler address
  uint16_t seg_selector;          //segment selector from GDT (0x8)
  uint16_t flags;                 //description below
  uint16_t offset_31_16;          //part of handler address
  uint32_t offset_63_32;            //part of handler address
  uint32_t reserved;                //reserved by cpu
};
typedef struct _IDTE IDTE;

//IST bits[0:2] - Interrupt Stack Table
//TYPE bits[8:11] - Table Intel 3A, page 102, table 3-2, interrupt desc gate for 64 bits
//DPL bits[13:14] - ring 0 permission
//P bit 15 - present

//TYPES
//0xE - interrupt gate - hardware int, disable further int
//0x6 - trap gate - software int, hardware int are still one

IDTE table[256];

struct _IDTP{
    uint16_t limit;
    uint64_t address;
} __attribute__((packed)) ;
typedef struct _IDTP IDTP;

extern void DivideError_Wrapper(void);
extern void BoundError_Wrapper(void);
extern void InvalidOpcodeError_Wrapper(void);

uint16_t SetIDTEntryFlags(uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p){
    return (uint16_t)(ist | (type << 8) | (dpl << 13) | (p << 15));
}

void SetIDTEntry(IDTE* idte, uint64_t address, uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p){
    idte->offset_63_32 = (address >> 32);
    idte->offset_31_16 = ((address & 0xFFFF0000) >> 16);
    idte->offset_15_0 = (address & 0xFFFF);
    idte->flags = SetIDTEntryFlags(ist, type, dpl, p);
    idte->seg_selector = 0x8;
}

void SetIDTR(void){
    SetIDTEntry(&table[0], (uint64_t)DivideError_Wrapper, 0, 0xE, 0, 1);
    SetIDTEntry(&table[5], (uint64_t)BoundError_Wrapper, 0, 0xE, 0, 1);
    SetIDTEntry(&table[6], (uint64_t)InvalidOpcodeError_Wrapper, 0, 0xE, 0, 1);

    //INTEL 3A, page 200
    IDTP idtp = {
        256*16-1,
        (uint64_t)&table
    };

    __asm("lidt %0" : : "m"(idtp));
}

//IDT SECTION END