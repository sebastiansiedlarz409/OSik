#ifndef HAL_H
#define HAL_H

void HAL_PortOutByte(int port, unsigned char v);
void HAL_PortOutWord(int port, unsigned short v);
void HAL_PortOutDword(int port, unsigned int v);

#endif //HAL_H