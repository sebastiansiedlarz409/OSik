#include "..\hal\hal.h"
#include "..\common.h"
#include "..\libs\memory.h"
#include "terminal.h"

#include <stdint.h>

#define LINE_WIDTH 160
#define LINE_COUNT 25

struct B8000_8025_Context {
  uint16_t x;
  uint16_t y;
  uint8_t style;
  uint8_t mode;
};

static struct B8000_8025_Context B8000_8025_context = {
    .mode = COMMAND,
    .style = 0x02
};

static void B8000_8025_Style(TerminalContext* context, uint8_t style)
{
    UNUSED(context);
    B8000_8025_context.style = style;
}

static void B8000_8025_Scp(TerminalContext* context, uint16_t x, uint16_t y)
{
    UNUSED(context);
    //http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_with_the_BIOS
    uint32_t position = y * (LINE_WIDTH/2) + x;

    HAL_PortOutByte(0x3D4, 0x0F);                                       //tell that we want change reg 0x0F in 0x3D5 port
    HAL_PortOutByte(0x3D5, (unsigned char)(position & 0xFF));           //lower 8 bits
    HAL_PortOutByte(0x3D4, 0x0E);
    HAL_PortOutByte(0x3D5, (unsigned char)(position >> 8));

    B8000_8025_context.x = x;
    B8000_8025_context.y = y;
}

static void B8000_8025_Scroll(TerminalContext* context)
{
    char *textVRAM = (char*)0xB8000;

    //copy memory
    MM_Mmove(textVRAM+LINE_WIDTH, textVRAM, LINE_COUNT*LINE_WIDTH-LINE_WIDTH);

    for(int i = LINE_COUNT*LINE_WIDTH-LINE_WIDTH;i<LINE_COUNT*LINE_WIDTH;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = B8000_8025_context.style;
    }

    B8000_8025_Scp(context, 0, LINE_COUNT-1);
}

static void B8000_8025_Gcp(TerminalContext* context, uint16_t* x, uint16_t* y)
{
    UNUSED(context);
    *x = B8000_8025_context.x;
    *y = B8000_8025_context.y;
}

static void B8000_8025_Gsize(TerminalContext* context, uint16_t* w, uint16_t* h)
{
    UNUSED(context);
    *w = LINE_WIDTH/2;
    *h = LINE_COUNT;
}

static void B8000_8025_Putchar(TerminalContext* context, char ch)
{
    char *textVRAM = (char*)0xB8000;

    uint16_t x = B8000_8025_context.x;
    uint16_t y = B8000_8025_context.y;

    if(y == LINE_COUNT){
        B8000_8025_Scroll(context);
        x = B8000_8025_context.x;
        y = B8000_8025_context.y;
    }

    uint32_t position = y * (LINE_WIDTH/2) + x;

    textVRAM[position*2] = ch;
    textVRAM[position*2+1] = B8000_8025_context.style;

    x++;

    if(x==80){
        x=0;
        y++;
    }

    B8000_8025_Scp(context, x,y);
}

static void B8000_8025_Removechar(TerminalContext* context)
{
    char *textVRAM = (char*)0xB8000;

    uint16_t x = B8000_8025_context.x;
    uint16_t y = B8000_8025_context.y;

    if(y == 0 && x == 0){
        return;
    }

    x--;

    if(x==0){
        x=80;
        y--;
    }

    B8000_8025_Scp(context, x, y);

    uint32_t position = y * (LINE_WIDTH/2) + x;

    textVRAM[position*2] = 0;
    textVRAM[position*2+1] = B8000_8025_context.style;
}

static void B8000_8025_Cls(TerminalContext* context)
{
    //write whole buffer with value 0x0002
    char *textVRAM = (char*)0xB8000;
    for(int i = 0;i<LINE_WIDTH*LINE_COUNT;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = B8000_8025_context.style;
    }

    //move cursor to 0, 0
    B8000_8025_Scp(context, 0, 0);
}

static uint8_t B8000_8025_GMode(TerminalContext* context)
{
    UNUSED(context);
    return B8000_8025_context.mode;
}

static void B8000_8025_TMode(TerminalContext* context)
{
    UNUSED(context);
    B8000_8025_context.mode = B8000_8025_context.mode == COMMAND ? DATA : COMMAND;
}

static const TerminalContext context = {
    ._scp = B8000_8025_Scp,
    ._gcp = B8000_8025_Gcp,
    ._clear = B8000_8025_Cls,
    ._putchar = B8000_8025_Putchar,
    ._removechar = B8000_8025_Removechar,
    ._gsize = B8000_8025_Gsize,
    ._style = B8000_8025_Style,
    ._tmode = B8000_8025_TMode,
    ._gmode = B8000_8025_GMode
};

TerminalContext* Terminal_B8000_8025_GetTerminalContext(void)
{
    return (TerminalContext*)&context;
}