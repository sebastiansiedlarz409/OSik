//objdump -d -M intel filename

#include "hal.h"

#define LINE_WIDTH 160
#define LINE_COUNT 25
#define CHAR_STYLE 0x02

//screen context
struct VRAM_ContextStruct {
  unsigned short x;
  unsigned short y;
} VRAM_Context;

//PORTS
//https://wiki.osdev.org/I/O_Ports
//http://bochs.sourceforge.net/techspec/PORTS.LST
//0x03B0-0x03DF
//how to use ports
//https://wiki.osdev.org/Port_IO
//inline assembly
//https://students.mimuw.edu.pl/SO/Projekt03-04/temat2-g6/inline.html

void _scp(unsigned short x, unsigned short y){
    //http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_with_the_BIOS
    unsigned int position = y * (LINE_WIDTH/2) + x;

    HAL_PortOutByte(0x3D4, 0x0F);                                       //tell that we want change reg 0x0F in 0x3D5 port
    HAL_PortOutByte(0x3D5, (unsigned char)(position & 0xFF));           //lower 8 bits
    HAL_PortOutByte(0x3D4, 0x0E);
    HAL_PortOutByte(0x3D5, (unsigned char)(position >> 8));

    VRAM_Context.x = x;
    VRAM_Context.y = y;
}

void _putchar(char ch){
    char *textVRAM = (char*)0xB8000;

    unsigned short x = VRAM_Context.x;
    unsigned short y = VRAM_Context.y;

    unsigned int position = y * (LINE_WIDTH/2) + x;

    textVRAM[position*2] = ch;
    textVRAM[position*2+1] = CHAR_STYLE;

    x++;

    if(x==80){
        x=0;
        y++;
    }
    _scp(x,y);
}

void _printf(char* value){
    while(*value != '\0'){

        if(*value == '\n'){
            _scp(VRAM_Context.x, VRAM_Context.y+1);
        }
        else if(*value == '\r'){
            _scp(0, VRAM_Context.y);
        }
        else if(*value == '\t'){
            unsigned short x = VRAM_Context.x;
            unsigned short y = VRAM_Context.y;

            x += 8 - x % 8;
            if (x >= 80) {
                x = 0;
                y += 1;
                _scp(x, y);          
            }
            else{
                for(unsigned short i = VRAM_Context.x; i < x; i++){
                    _putchar(' ');
                }
            }
        }
        else{
            _putchar(*value);
        }

        value++;
        
    }
}

void _cls(void){
    //write whole buffer with value 0x0002
    char *textVRAM = (char*)0xB8000;
    for(int i = 0;i<LINE_WIDTH*LINE_COUNT;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = CHAR_STYLE;
    }

    //move cursor to 0, 0
    _scp(0, 0);
}

void _printfAddress(void* address){
    unsigned long long sAddress = (unsigned long long)address;

    for(int i = 0; i < 32; i+=2){
        _putchar("0123456789ABCDEF"[(sAddress >> 60) & 0xf]);
        sAddress <<= 4;
    }
}

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    
    _printf("Kernel loaded at 0x");
    _printfAddress(kernelEntryPointAddress);

    _printf("\r\nStack pointer at 0x");
    _printfAddress(stackAddress);
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    _cls();
    
    _welcome(kernelEntryPointAddress, stackAddress);

    for(;;);
}