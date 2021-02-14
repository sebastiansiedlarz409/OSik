#ifndef CALC_H
#define CALC_H

#include <stdint.h>

uint8_t CALC_Execute(const char* exp);
uint8_t CALC_Eval(char* parse);

#endif //CALC_H