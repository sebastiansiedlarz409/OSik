#include "error.h"
#include "..\int\interrupt_handlers.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

TerminalContext* context;

void BSOD(const char* reason, TrapFrame* frame){
    context = Terminal_B8000_8025_GetTerminalContext();

    T_StyleTerminal(context, 0x17);
    T_ClearTerminal(context);
    print(context, "%s\n\r", reason);
    print(context, "RSP -> %x\n\r", frame->rsp);
    print(context, "RAX -> %x\n\r", frame->rax);
    print(context, "RBX -> %x\n\r", frame->rbx);
    print(context, "RCX -> %x\n\r", frame->rcx);
    print(context, "RDX -> %x\n\r", frame->rdx);
    print(context, "RSI -> %x\n\r", frame->rsi);
    print(context, "RDI -> %x\n\r", frame->rdi);
    print(context, "RBB -> %x\n\r", frame->rbp);
    print(context, "R8  -> %x\n\r", frame->r8);
    print(context, "R9  -> %x\n\r", frame->r9);
    print(context, "R10 -> %x\n\r", frame->r10);
    print(context, "R11 -> %x\n\r", frame->r11);
    print(context, "R12 -> %x\n\r", frame->r12);
    print(context, "R13 -> %x\n\r", frame->r13);
    print(context, "R14 -> %x\n\r", frame->r14);
    print(context, "R15 -> %x\n\r", frame->r15);
    print(context, "RIP -> %x\n\r", frame->rip);
    print(context, "SEG -> %x\n\r", frame->segment_cs);

    for(;;);
}