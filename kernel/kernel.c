//objdump -d -M intel filename
#include "hal\hal.h"
#include "common.h"
#include "int\interrupt.h"
#include "terminal\terminal.h"
#include "terminal\terminal_B8000_8025.h"

#include <stdint.h>

TerminalContext* context;

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    uint64_t SAddr = (uint64_t)stackAddress;

    print(context, "Kernel loaded at 0x%x\n\r", KEPAddr);
    print(context, "Stack pointer at 0x%x\n\r", SAddr);
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    //set interrupts
    INT_SetIDTR();

    context = Terminal_B8000_8025_GetTerminalContext();

    T_ClearTerminal(context);
    _welcome(kernelEntryPointAddress, stackAddress);

    //test int 0
    /*int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));*/

    for(;;);
}