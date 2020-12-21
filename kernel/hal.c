#include "hal.h"

//PORTS
//https://wiki.osdev.org/I/O_Ports
//http://bochs.sourceforge.net/techspec/PORTS.LST
//0x03B0-0x03DF
//how to use ports
//https://wiki.osdev.org/Port_IO
//inline assembly
//https://students.mimuw.edu.pl/SO/Projekt03-04/temat2-g6/inline.html

void HAL_PortOutByte(int port, unsigned char v) {
  __asm("out dx, al\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutWord(int port, unsigned short v) {
  __asm("out dx, ax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutDword(int port, unsigned int v) {
  __asm("out dx, eax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}