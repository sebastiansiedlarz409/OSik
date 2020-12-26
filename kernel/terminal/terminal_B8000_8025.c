#include "..\hal\hal.h"
#include "..\common.h"
#include "..\lib\memory.h"
#include "terminal.h"

#include <stdint.h>

#define LINE_WIDTH 160
#define LINE_COUNT 25

static struct VRAM_ContextStruct {
  uint16_t x;
  uint16_t y;
  uint8_t style;
} VRAM_Context;

static void _style(TerminalContext* context, uint8_t style){
    UNUSED(context);
    VRAM_Context.style = style;
}

static void _scp(TerminalContext* context, uint16_t x, uint16_t y){
    UNUSED(context);
    //http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_with_the_BIOS
    uint32_t position = y * (LINE_WIDTH/2) + x;

    HAL_PortOutByte(0x3D4, 0x0F);                                       //tell that we want change reg 0x0F in 0x3D5 port
    HAL_PortOutByte(0x3D5, (unsigned char)(position & 0xFF));           //lower 8 bits
    HAL_PortOutByte(0x3D4, 0x0E);
    HAL_PortOutByte(0x3D5, (unsigned char)(position >> 8));

    VRAM_Context.x = x;
    VRAM_Context.y = y;
}

static void _scroll(TerminalContext* context){
    char *textVRAM = (char*)0xB8000;

    //copy memory
    memmove(textVRAM+LINE_WIDTH, textVRAM, LINE_COUNT*LINE_WIDTH-LINE_WIDTH);

    for(int i = LINE_COUNT*LINE_WIDTH-LINE_WIDTH;i<LINE_COUNT*LINE_WIDTH;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = VRAM_Context.style;
    }

    _scp(context, 0, LINE_COUNT-1);
}

static void _gcp(TerminalContext* context, uint16_t* x, uint16_t* y){
    UNUSED(context);
    *x = VRAM_Context.x;
    *y = VRAM_Context.y;
}

static void _gsize(TerminalContext* context, uint16_t* w, uint16_t* h){
    UNUSED(context);
    *w = LINE_WIDTH/2;
    *h = LINE_COUNT;
}

static void _putchar(TerminalContext* context, char ch){
    char *textVRAM = (char*)0xB8000;

    uint16_t x = VRAM_Context.x;
    uint16_t y = VRAM_Context.y;

    if(y == LINE_COUNT){
        _scroll(context);
        x = VRAM_Context.x;
        y = VRAM_Context.y;
    }

    uint32_t position = y * (LINE_WIDTH/2) + x;

    textVRAM[position*2] = ch;
    textVRAM[position*2+1] = VRAM_Context.style;

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
        textVRAM[i+1] = VRAM_Context.style;
    }

    //move cursor to 0, 0
    _scp(context, 0, 0);
}

static const TerminalContext context = {
    ._scp = _scp,
    ._gcp = _gcp,
    ._clear = _cls,
    ._putchar = _putchar,
    ._gsize = _gsize,
    ._style = _style
};

TerminalContext* Terminal_B8000_8025_GetTerminalContext(void){
    VRAM_Context.style = 0x02;
    return (TerminalContext*)&context;
}