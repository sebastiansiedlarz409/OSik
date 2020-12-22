#include "terminal.h"
#include "common.h"

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

void T_PrintfChar(TerminalContext* context, char ch){
    char temp[2] = {ch, '\0'};
    T_PutText(context, temp);
}

void T_PrintfUInt(TerminalContext* context, size_t ch){
    if(ch == 0){
        T_PrintfChar(context, '0');
        return;
    }

    char buf[24] = {0};
    char *p = &buf[24];
    while (ch != 0) {
        --p;
        *p = (ch % 10) + '0';
        ch /= 10;
    }
    T_PutText(context, p);
}

void T_PrintfInt(TerminalContext *context, long long ch) {
  if (ch == (-9223372036854775807LL - 1LL)) {
    T_PutText(context, "-9223372036854775808");
    return;
  }

  if (ch < 0) {
    T_PutChar(context, '-');
    ch = -ch;
  }

  if (ch == 0) {
    T_PutChar(context, '0');
    return;
  }

  char buf[24] = {0};
  char *p = &buf[23];
  while (ch != 0) {
    --p;
    *p = (ch % 10) + '0';
    ch /= 10;
  }
  T_PutText(context, p);
}

void T_PrintfHex(TerminalContext *context, size_t ch, int width) {
  if (ch == 0) {
    T_PutChar(context, '0');
    return;
  }

  int sh = 0;
  while (width < 16 - sh && (ch & 0xF000000000000000ULL) == 0) {
    sh ++;
    ch <<= 4;
  }

  while (sh < 16) {
    size_t idx = (ch & 0xF000000000000000ULL) >> 60;
    T_PutChar(context, "0123456789ABCDEF"[idx]);
    sh ++;
    ch <<= 4;
  }
}