#include "string.h"

#include <stdint.h>

uint8_t STR_CMP(const char* str0, const char* str1){
    uint8_t result = 1;
    while(1){
        if(*str0 != *str1){
            result = 0;
            break;
        }
        if(*str0 == '\0'){
            break;
        }
        if(*str1 == '\0'){
            break;
        }
        str0++;
        str1++;
    }

    return result;
}