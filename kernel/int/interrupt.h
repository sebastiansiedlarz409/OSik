#ifndef INTERRUPT_H
#define INTERRUPT_H

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

void INT_SetIDTR(void);

#endif //INTERRUPT_H