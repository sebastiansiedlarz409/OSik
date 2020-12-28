#include "../hal/hal.h"
#include "../int/pic.h"
#include "keyboard.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

TerminalContext* context;

typedef struct _KB_Context{
    uint8_t counter;
} KB_Context;

KB_Context kb_context = {
    .counter = 0
};

char KB_GetChar(uint8_t scanCode)
{
    if(scanCode >= 0x81)
        scanCode -= 0x24;

    return scanCodeCh[scanCode];
}

void KB_Print(uint8_t scanCode)
{
    char ch = KB_GetChar(scanCode);

    if(kb_context.counter == 0){
        T_PutChar(context, ch);
        kb_context.counter++;
    }
    else{
        kb_context.counter = 0;
    }
}

void KB_Interrupt(void)
{
    context = Terminal_B8000_8025_GetTerminalContext();

    uint8_t scanCode;
    HAL_PortInByte(0x60, &scanCode);

    KB_Print(scanCode);

    PIC_ClearInt();
}