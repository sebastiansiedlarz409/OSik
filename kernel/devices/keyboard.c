#include "../hal/hal.h"
#include "../int/pic.h"
#include "keyboard.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

TerminalContext* context;

void KB_Interrupt(void)
{
    uint8_t temp;
    HAL_PortInByte(0x60, &temp);

    context = Terminal_B8000_8025_GetTerminalContext();

    T_PutChar(context, 'a');

    PIC_ClearInt();
}