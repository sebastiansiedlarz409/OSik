//objdump -d -M intel filename
#include "logo.h"
#include "hal\hal.h"
#include "common.h"
#include "int\interrupt.h"
#include "devices\pit.h"
#include "libs\heap.h"
#include "terminal\terminal.h"
#include "terminal\terminal_B8000_8025.h"

#include <stdint.h>

TerminalContext* context;

void KERN_Welcome(void* kernelEntryPointAddress, void* stackAddress)
{
    uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    uint64_t SAddr = (uint64_t)stackAddress;

    LOGO_ShowLogo();

    //void* p1 = HEAP_Malloc(20);
    //void* p2 = HEAP_Malloc(20);
    //HEAP_Free(p2);
    //void* p3 = HEAP_Malloc(20);
    //void* p4 = HEAP_Malloc(5);

    //print(context, "%x\r\n", (long long)p1);
    //print(context, "%x\r\n", (long long)p2);
    //print(context, "%x\r\n", (long long)p3);
    //print(context, "%x\r\n", (long long)p4);

    print(context, "Kernel loaded at 0x%x\n\r", KEPAddr);
    print(context, "Stack pointer at 0x%x\n\r", SAddr);
    print(context, "[ESC] to clear screen\n\r");
    print(context, "[F1/F2/...] to style terminal\n\r");

    T_StyleTerminal(context, 0x0F);

    print(context, "%c", terminalChar);
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress)
{
    //set interrupts
    INT_SetIDTR();
    
    //init heap
    HEAP_Init(0x500000, 0x100000);

    //PIT sleep
    PIT_Sleep(2000);

    context = Terminal_B8000_8025_GetTerminalContext();

    T_ClearTerminal(context);
    KERN_Welcome(kernelEntryPointAddress, stackAddress);

    //test int 0
    int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));

    for(;;);
}