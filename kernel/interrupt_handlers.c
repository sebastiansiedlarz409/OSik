#include "error.h"
#include "interrupt_handlers.h"

__attribute__((interrupt)) void DivideError_Handler(TrapFrame *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}