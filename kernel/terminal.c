#include "terminal.h"

void T_SetCursorPosition(TerminalContext* context, unsigned short x, unsigned short y){
    context->_scp(context, x, y);
}

void T_GetCursorPosition(TerminalContext* context, unsigned short* x, unsigned short* y){
    context->_gcp(context, x, y);
}

void T_ClearTerminal(TerminalContext* context){
    context->_clear(context);
}

void T_GetTerminalSize(TerminalContext* context, unsigned short* w, unsigned short* h){
    context->_gsize(context, w, h);
}

void T_PutChar(TerminalContext* context, char ch){
    context->_putchar(context, ch);
}

void T_PutText(TerminalContext* context, const char *value){
    unsigned short x;
    unsigned short y;
    unsigned short xb;
    unsigned short yb;
    unsigned short w;
    unsigned short h;

    while(*value != '\0'){

        if(*value == '\n'){
            T_GetCursorPosition(context, &x, &y);
            T_SetCursorPosition(context, x, y+1);
        }
        else if(*value == '\r'){
            T_GetCursorPosition(context, &x, &y);
            T_SetCursorPosition(context, 0, y);
        }
        else if(*value == '\t'){
            T_GetCursorPosition(context, &xb, &yb);
            T_GetTerminalSize(context, &w, &h);
            x = xb;
            y = yb;

            x += 8 - x % 8;
            if (x >= w) {
                x = 0;
                y += 1;
                T_SetCursorPosition(context, x, y);          
            }
            else{
                for(unsigned short i = xb; i < x; i++){
                    T_PutChar(context, ' ');
                }
            }
        }
        else{
            T_PutChar(context, *value);
        }

        value++;  
    }
}

void printfChar(TerminalContext* context, char ch){
    char temp[2] = {ch, '\0'};
    T_PutText(context, temp);
}