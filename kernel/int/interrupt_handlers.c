#include "error.h"
#include "interrupt_handlers.h"

void DivideError_Handler(void *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}

void BoundError_Handler(void *trapFrame)
{
    BSOD("BOUND ERROR", trapFrame);
}

void InvalidOpcodeError_Handler(void *trapFrame)
{
    BSOD("INVALID OPCODE ERROR", trapFrame);
}