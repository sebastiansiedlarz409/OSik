#include "../common.h"
#include "error.h"
#include "interrupt_handlers.h"
#include "../int/pic.h"
#include "../hal/hal.h"
#include "../int/pic.h"
#include "../devices/pit.h"
#include "../devices/keyboard.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

//https://wiki.osdev.org/Exceptions

void DivideError_Handler(void *trapFrame)
{
    BSOD("DIVIDE BY ZERO ERROR", trapFrame);
}

void KeyboardInt_Handler(void* trapFrame)
{
    UNUSED(trapFrame);
    KB_Interrupt();
    PIC_ClearInt();
}

void PITInt_Handler(void* trapFrame)
{
    UNUSED(trapFrame);
    PIT_Count();
}