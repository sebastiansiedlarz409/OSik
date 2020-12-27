#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>

void DivideError_Handler(void* frame);
void BoundError_Handler(void* frame);
void InvalidOpcodeError_Handler(void* frame);

#endif //INTERRUPT_HANDLER_H