#include "error.h"
#include "..\int\interrupt_handlers.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

TerminalContext* context;

void BSOD(const char* reason, void* frame)
{
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
    uint64_t eflags = *(frameBuffer+16);
    uint64_t rip = *(frameBuffer+17);

    T_StyleTerminal(context, 0x17);
    T_ClearTerminal(context);

    print(context, "!!!I have died!!!\r\n\r\n");

    print(context, "%s\n\r\r\n", reason);
    
    print(context, "R15 -> %x \t RBP -> %x\r\n", r15, rbp);
    print(context, "R14 -> %x \t RDI -> %x\r\n", r14, rdi);
    print(context, "R13 -> %x \t RSI -> %x\r\n", r13, rsi);
    print(context, "R12 -> %x \t RDX -> %x\r\n", r12, rdx);
    print(context, "R11 -> %x \t RCX -> %x\r\n", r11, rcx);
    print(context, "R10 -> %x \t RBX -> %x\r\n", r10, rbx);
    print(context, "R9  -> %x \t RAX -> %x\r\n", r9, rax);
    print(context, "R8  -> %x \t RSP -> %x\r\n", r8, rsp);
    print(context, "RIP -> %x\r\n\r\n", rip);

    print(context, "EFLAGS -> %x %d%d%d%d%d%d%d%d\r\n", eflags,
     (eflags&128) >> 7, (eflags&64) >> 6 ,(eflags&32) >> 5,(eflags&16) >> 4,
     (eflags&8) >> 3,(eflags&4) >> 2,(eflags&2) >> 1,(eflags&1));

    for(;;);
}