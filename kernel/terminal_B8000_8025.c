#include "hal.h"
#include "terminal.h"

#define LINE_WIDTH 160
#define LINE_COUNT 25
#define CHAR_STYLE 0x02

static struct VRAM_ContextStruct {
  unsigned short x;
  unsigned short y;
} VRAM_Context;

static void _scp(TerminalContext* context, unsigned short x, unsigned short y){
    //http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_with_the_BIOS
    unsigned int position = y * (LINE_WIDTH/2) + x;

    HAL_PortOutByte(0x3D4, 0x0F);                                       //tell that we want change reg 0x0F in 0x3D5 port
    HAL_PortOutByte(0x3D5, (unsigned char)(position & 0xFF));           //lower 8 bits
    HAL_PortOutByte(0x3D4, 0x0E);
    HAL_PortOutByte(0x3D5, (unsigned char)(position >> 8));

    VRAM_Context.x = x;
    VRAM_Context.y = y;
}

static void _gcp(TerminalContext* context, unsigned short* x, unsigned short* y){
    *x = VRAM_Context.x;
    *y = VRAM_Context.y;
}

static void _gsize(TerminalContext* context, unsigned short* w, unsigned short* h){
    *w = LINE_WIDTH/2;
    *h = LINE_COUNT;
}

static void _putchar(TerminalContext* context, char ch){
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
    _scp(context, x,y);
}

static void _cls(TerminalContext* context){
    //write whole buffer with value 0x0002
    char *textVRAM = (char*)0xB8000;
    for(int i = 0;i<LINE_WIDTH*LINE_COUNT;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = CHAR_STYLE;
    }

    //move cursor to 0, 0
    _scp(context, 0, 0);
}

static const TerminalContext context = {
    ._scp = _scp,
    ._gcp = _gcp,
    ._clear = _cls,
    ._putchar = _putchar,
    ._gsize = _gsize
};

TerminalContext* Terminal_B8000_8025_GetTerminalContext(void){
    return (TerminalContext*)&context;
}