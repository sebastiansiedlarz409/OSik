#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct _terminalContext{
    void (*_scp)(TerminalContext* context, unsigned short x, unsigned short y);
    void (*_gcp)(TerminalContext* context, unsigned short* x, unsigned short* y);
    void (*_clear)(TerminalContext* context);
    void (*_putchar)(TerminalContext* context, char ch);
    void (*_gsize)(TerminalContext* context, unsigned short* w, unsigned short* h);
} TerminalContext;

void T_SetCursorPosition(TerminalContext* context, unsigned short x, unsigned short y);
void T_GetCursorPosition(TerminalContext* context, unsigned short* x, unsigned short* y);
void T_ClearTerminal(TerminalContext* context);
void T_PutChar(TerminalContext* context, char ch);
void T_GetTerminalSize(TerminalContext* context, unsigned short* w, unsigned short* h);
void T_PutText(TerminalContext* context, const char *value);

#endif //TERMINAL_H
