#include "error.h"
#include "interrupt_handlers.h"
#include "../hal/hal.h"
#include "../int/pic.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

//https://wiki.osdev.org/Exceptions

void DivideError_Handler(void *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}

void KeyboardInt_Handler(void* trapFrame)
{
    uint8_t temp;
    HAL_PortInByte(0x60, &temp);

    TerminalContext* context = Terminal_B8000_8025_GetTerminalContext();

    T_PutChar(context, 'a');

    PIC_ClearInt(0x1);
}