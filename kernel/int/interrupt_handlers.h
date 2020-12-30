#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

void DivideError_Handler(void* trapFrame);
void KeyboardInt_Handler(void* trapFrame);
void PITInt_Handler(void* trapFrame);

#endif //INTERRUPT_HANDLER_H