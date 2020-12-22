#ifndef TERMINAL_H
#define TERMINAL_H

#include "common.h"

struct TerminalBackend;
typedef struct _terminalContext TerminalContext;

struct _terminalContext{
    void (*_scp)(TerminalContext* context, unsigned short x, unsigned short y);
    void (*_gcp)(TerminalContext* context, unsigned short* x, unsigned short* y);
    void (*_clear)(TerminalContext* context);
    void (*_putchar)(TerminalContext* context, char ch);
    void (*_gsize)(TerminalContext* context, unsigned short* w, unsigned short* h);
};

void T_SetCursorPosition(TerminalContext* context, unsigned short x, unsigned short y);
void T_GetCursorPosition(TerminalContext* context, unsigned short* x, unsigned short* y);
void T_ClearTerminal(TerminalContext* context);
void T_PutChar(TerminalContext* context, char ch);
void T_GetTerminalSize(TerminalContext* context, unsigned short* w, unsigned short* h);
void T_PutText(TerminalContext* context, const char *value);
void T_PrintfChar(TerminalContext* context, char ch);
void T_PrintfUInt(TerminalContext* context, size_t ch);
void T_PrintfInt(TerminalContext *tb, long long ch);
void T_PrintfHex(TerminalContext *context, size_t ch, int width);
void printf(TerminalContext* context, const char *formatString, ...);

#endif //TERMINAL_H
