//objdump -d -M intel filename

#include "hal.h"
#include "terminal.h"

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    
    /*_printf("Kernel loaded at 0x");
    _printfAddress(kernelEntryPointAddress);

    _printf("\r\nStack pointer at 0x");
    _printfAddress(stackAddress);*/
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    //_cls();
    
    _welcome(kernelEntryPointAddress, stackAddress);

    for(;;);
}