#include "string.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

#include <stdint.h>

uint8_t STR_CMP(const char* str0, const char* str1){
    uint8_t result = 1;

    char* str0b = (char*)str0;
    char* str1b = (char*)str1;

    while(1){
        if(*str0b != *str1b){
            result = 0;
            break;
        }
        if(*str0b == '\0'){
            break;
        }
        if(*str1b == '\0'){
            break;
        }
        //print(Terminal_B8000_8025_GetTerminalContext(), "%c %c %u\n\r", *str0b, *str1b, result);
        str0b++;
        str1b++;
    }

    return result;
}