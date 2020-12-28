#include <stdint.h>

#include "hal.h"

//PORTS
//https://wiki.osdev.org/I/O_Ports
//http://bochs.sourceforge.net/techspec/PORTS.LST
//0x03B0-0x03DF
//how to use ports
//https://wiki.osdev.org/Port_IO
//inline assembly
//https://students.mimuw.edu.pl/SO/Projekt03-04/temat2-g6/inline.html

void HAL_PortOutByte(uint32_t port, uint8_t v) {
  __asm("out dx, al\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutWord(uint32_t port, uint16_t v) {
  __asm("out dx, ax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutDword(uint32_t port, uint32_t v) {
  __asm("out dx, eax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortInByte(uint32_t port, uint8_t* v) {
  __asm("in al, dx\n" : /*output var*/ "=a" (*v): /*input var*/ "d" (port) : /*clear regs*/);
}

void HAL_PortInWord(uint32_t port, uint16_t* v) {
  __asm("in ax, dx\n" : /*output var*/ "=a" (*v) : /*input var*/ "d" (port) : /*clear regs*/);
}

void HAL_PortInDword(uint32_t port, uint32_t* v) {
  __asm("in eax, dx\n" : /*output var*/ "=a" (*v) : /*input var*/ "d" (port) : /*clear regs*/);
}

void HAL_WaitIO(void){
  __asm__ volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}