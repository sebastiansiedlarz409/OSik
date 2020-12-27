#include "error.h"
#include "..\int\interrupt_handlers.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

TerminalContext* context;

void BSOD(const char* reason, void* frame){
    context = Terminal_B8000_8025_GetTerminalContext();

    uint64_t* frameBuffer = (uint64_t*)frame;

    uint64_t r15 = *(frameBuffer);
    uint64_t r14 = *(frameBuffer+1);
    uint64_t r13 = *(frameBuffer+2);
    uint64_t r12 = *(frameBuffer+3);
    uint64_t r11 = *(frameBuffer+4);
    uint64_t r10 = *(frameBuffer+5);
    uint64_t r9 = *(frameBuffer+6);
    uint64_t r8 = *(frameBuffer+7);
    uint64_t rbp = *(frameBuffer+8);
    uint64_t rdi = *(frameBuffer+9);
    uint64_t rsi = *(frameBuffer+10);
    uint64_t rdx = *(frameBuffer+11);
    uint64_t rcx = *(frameBuffer+12);
    uint64_t rbx = *(frameBuffer+13);
    uint64_t rax = *(frameBuffer+14);
    uint64_t rsp = *(frameBuffer+15);
    uint64_t rip = *(frameBuffer+16);

    T_StyleTerminal(context, 0x17);
    T_ClearTerminal(context);
    print(context, "%s\n\r", reason);
    print(context, "R15 -> %x\r\n", r15);
    print(context, "R14 -> %x\r\n", r14);
    print(context, "R13 -> %x\r\n", r13);
    print(context, "R12 -> %x\r\n", r12);
    print(context, "R11 -> %x\r\n", r11);
    print(context, "R10 -> %x\r\n", r10);
    print(context, "R9  -> %x\r\n", r9);
    print(context, "R8  -> %x\r\n", r8);
    print(context, "RBP -> %x\r\n", rbp);
    print(context, "RDI -> %x\r\n", rdi);
    print(context, "RSI -> %x\r\n", rsi);
    print(context, "RDX -> %x\r\n", rdx);
    print(context, "RCX -> %x\r\n", rcx);
    print(context, "RBX -> %x\r\n", rbx);
    print(context, "RAX -> %x\r\n", rax);
    print(context, "RSP -> %x\r\n", rsp);
    print(context, "RIP -> %x\r\n", rip);

    for(;;);
}