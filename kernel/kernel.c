//objdump -d -M intel filename

#include "hal.h"
#include "common.h"
#include "terminal.h"
#include "terminal_B8000_8025.h"

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    
    /*_printf("Kernel loaded at 0x");
    _printfAddress(kernelEntryPointAddress);

    _printf("\r\nStack pointer at 0x");
    _printfAddress(stackAddress);*/
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    TerminalContext* context = Terminal_B8000_8025_GetTerminalContext();

    T_ClearTerminal(context);
    T_PrintfHex(context, 0x1F, 8);
    //_welcome(kernelEntryPointAddress, stackAddress);

    for(;;);
}