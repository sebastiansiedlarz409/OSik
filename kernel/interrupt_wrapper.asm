global DivideError_Wrapper

extern DivideError_Handler

section .text
DivideError_Wrapper:
    cld
    call DivideError_Handler
    iretq