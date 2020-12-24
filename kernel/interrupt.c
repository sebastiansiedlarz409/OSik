#include "interrupt.h"

//IDT SECTION

//INTERRUPT -> Intel 3A, page 199, chapter 6
//FOR LONG MODE -> Intel 3A, page 210m chapter 6.14
//Interrupt list -> Intel 3A, page 192

typedef struct _IDTE {
  unsigned short offset_15_0;           //part of handler address
  unsigned short seg_selector;          //segment selector from GDT (0x8)
  unsigned short flags;                 //description below
  unsigned short offset_31_16;          //part of handler address
  unsigned int offset_63_32;            //part of handler address
  unsigned int reserved;                //reserved by cpu
} IDTE;

//IST bits[0:2] - Interrupt Stack Table
//TYPE bits[8:11] - Table Intel 3A, page 102, table 3-2, interrupt desc gate for 64 bits
//DPL bits[13:14] - ring 0 permission
//P bit 15 - present

//TYPES
//0xE - interrupt gate - hardware int, disable further int
//0x6 - trap gate - software int, hardware int are still one

IDTE table[256];

typedef struct _IDTP{
    unsigned short limit;
    unsigned long long address;
} IDTP;

unsigned short SetIDTEntryFlags(unsigned char ist, unsigned char type, unsigned char dpl, unsigned char p){
    ist &= 0b00000111;
    type &= 0b00001111;
    dpl &= 0b00000111;
    p &= 0b00000001;

    return ist | (type << 8) | (dpl << 13) | (p << 15);
}

void SetIDTEntry(IDTE* idte, unsigned long long address, unsigned char ist, unsigned char type, unsigned char dpl, unsigned char p){
    unsigned short flags = SetIDTEntryFlags(ist, type, dpl, p);
    idte->offset_63_32 = (address >> 32);
    idte->offset_31_16 = ((address && 0xFFFF0000) >> 16);
    idte->offset_15_0 = (address && 0xFFFF);
    idte->flags = flags;
    idte->seg_selector = 0x8;
}

//IDT SECTION END