#include "error.h"
#include "interrupt_handlers.h"

//https://wiki.osdev.org/Exceptions

void DivideError_Handler(void *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}