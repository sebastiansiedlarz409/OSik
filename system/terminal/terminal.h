#ifndef TERMINAL_H
#define TERMINAL_H

#include "..\common.h"

#include <stdint.h>

enum TerminalMode{
    COMMAND = 0x1,
    DATA = 0x2
};

typedef struct _terminalContext TerminalContext;

struct _terminalContext{
    void (*_scp)(TerminalContext* context, uint16_t x, uint16_t y);
    void (*_gcp)(TerminalContext* context, uint16_t* x, uint16_t* y);
    void (*_clear)(TerminalContext* context);
    uint8_t (*_getchar)(TerminalContext* context);
    void (*_putchar)(TerminalContext* context, char ch);
    void (*_removechar)(TerminalContext* context);
    void (*_gsize)(TerminalContext* context, uint16_t* w, uint16_t* h);
    void (*_style)(TerminalContext* context, uint8_t style);
    void (*_tmode)(TerminalContext* context);
    uint8_t (*_gmode)(TerminalContext* context);
};

void T_SetCursorPosition(TerminalContext* context, uint16_t x, uint16_t y);
void T_GetCursorPosition(TerminalContext* context, uint16_t* x, uint16_t* y);
void T_ClearTerminal(TerminalContext* context);
void T_PutChar(TerminalContext* context, char ch);
uint8_t T_GetChar(TerminalContext* context);
void T_GetTerminalSize(TerminalContext* context, uint16_t* w, uint16_t* h);
void T_PutText(TerminalContext* context, const char *value);
void T_PrintfChar(TerminalContext* context, char ch);
void T_PrintfUInt(TerminalContext* context, size_t ch);
void T_PrintfInt(TerminalContext *tb, int64_t ch);
void T_PrintfHex(TerminalContext *context, size_t ch, uint32_t width);
void T_StyleTerminal(TerminalContext *context, uint8_t style);
void T_NewLine(TerminalContext* context);
void T_RemoveChar(TerminalContext *context);
void T_TMode(TerminalContext* context);
uint8_t T_GMode(TerminalContext* context);
void print(TerminalContext* context, const char *formatString, ...);

#endif //TERMINAL_H
