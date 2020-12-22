//objdump -d -M intel filename

#include "hal.h"
#include "common.h"
#include "terminal.h"
#include "terminal_B8000_8025.h"

TerminalContext* context;

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    unsigned long long KEPAddr = (unsigned long long)kernelEntryPointAddress;
    unsigned long long SAddr = (unsigned long long)stackAddress;
    printf(context, "Kernel loaded at 0x%x\n\r", KEPAddr);

    printf(context, "Stack pointer at 0x%x\n\r", SAddr);
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    context = Terminal_B8000_8025_GetTerminalContext();

    T_ClearTerminal(context);
    _welcome(kernelEntryPointAddress, stackAddress);

    for(;;);
}