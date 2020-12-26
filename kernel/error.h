#ifndef ERROR_H
#define ERROR_H

#include "interrupt_handlers.h"

void BSOD(const char* reason, TrapFrame* frame);

#endif //ERROR_H