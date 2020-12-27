#include "error.h"
#include "interrupt_handlers.h"

void DivideError_Handler(void *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}