#include "error.h"
#include "interrupt_handlers.h"

//https://wiki.osdev.org/Exceptions

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

void DeviceNotAvailableError_Handler(void *trapFrame)
{
    BSOD("DEVICE NOT AVAILABLE [FPU] ERROR", trapFrame);
}

void InvalidTSSError_Handler(void *trapFrame)
{
    BSOD("INVALID TSS ERROR", trapFrame);
}