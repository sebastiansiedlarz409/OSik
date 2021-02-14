#include "calc.h"
#include "..\libs\heap.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

#include <stdint.h>

uint8_t CALC_Execute(const char* exp){
    char* expression = (char*)exp;
    print(Terminal_B8000_8025_GetTerminalContext(), "Result: %c\n\r", expression[0]);
    CALC_Eval(expression);

    return 1;
}

uint8_t CALC_Eval(char* parse){
    //calculate size
    uint32_t size = 1;
    char* parseb = parse;
    while(*parseb!='\0'){
        parseb++;
        size++;
    }

    //skip calc commad
    while(*parse != '['){
        parse++;
    }
    parse++;

    //calculate operand size
    uint32_t operand_size = 1;
    parseb = parse;
    while(*parseb!=']'){
        parseb++;
        operand_size++;
    }

    uint8_t* exp = HEAP_Malloc(operand_size);
    for(uint32_t i = 0; i< operand_size;i++){
        exp[i] = *parse;
        parse++;
    }
    exp[operand_size-1] = '\0';

    print(Terminal_B8000_8025_GetTerminalContext(), "%u %c %c %c", operand_size, exp[0], exp[1], exp[2]);

    return 1;
}