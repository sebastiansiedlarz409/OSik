#include "interrupt_handlers.h"
#include "terminal.h"
#include "terminal_B8000_8025.h"

TerminalContext* context;

void DivideError_Handler(void){
    context = Terminal_B8000_8025_GetTerminalContext();

    printf(context, "DIVIDE BY ZERO ERROR\n\r");

    for(;;);
}