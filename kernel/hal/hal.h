#ifndef HAL_H
#define HAL_H

#include <stdint.h>

void HAL_PortOutByte(uint32_t port, uint8_t v);
void HAL_PortOutWord(uint32_t port, uint16_t v);
void HAL_PortOutDword(uint32_t port, uint32_t v);
void HAL_PortInByte(uint32_t port, uint8_t* v);
void HAL_PortInWord(uint32_t port, uint16_t* v);
void HAL_PortInDword(uint32_t port, uint32_t* v);
void HAL_WaitIO(void);

#endif //HAL_H