#include "calc.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

#include <stdint.h>

uint8_t CALC_Execute(const char* exp){
    char* expression = (char*)exp;
    print(Terminal_B8000_8025_GetTerminalContext(), "%c", expression[0]);
    //CALC_Eval(expression);

    return 1;
}

void CALC_Eval(char* parse){

}