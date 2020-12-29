#ifndef PIT_H
#define PIT_H

#include <stdint.h>

uint8_t PIT_COUNTER = 0;

void IncreaseTick(void);

#endif //PIT_H