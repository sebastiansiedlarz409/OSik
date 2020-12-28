//https://wiki.osdev.org/Programmable_Interval_Timer

#include "pit.h"
#include "../hal/hal.h"

#include <stdint.h>

void InitPIT(void){
    
}

void IncreaseTick(void){
    PIT_COUNTER++;
}

uint64_t GetTick(void){
    return PIT_COUNTER;
}