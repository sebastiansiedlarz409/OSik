#ifndef TERMINAL_B8000_8021
#define TERMINAL_B8000_8021

#include "terminal.h"

#include <stdint.h>

TerminalContext* Terminal_B8000_8025_GetTerminalContext(void);
uint8_t B8000_8025_GMode(TerminalContext* context);
void B8000_8025_TMode(TerminalContext* context);

#endif //TERMINAL_B8000_8021