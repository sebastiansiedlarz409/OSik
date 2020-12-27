#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>

void DivideError_Handler(void* trapFrame);
void BoundError_Handler(void* trapFrame);
void InvalidOpcodeError_Handler(void* trapFrame);
void DeviceNotAvailableError_Handler(void *trapFrame);
void InvalidTSSError_Handler(void *trapFrame);

#endif //INTERRUPT_HANDLER_H