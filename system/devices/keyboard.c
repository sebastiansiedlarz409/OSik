#include "..\hal\hal.h"
#include "..\cli\cli.h"
#include "keyboard.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

#include <stdint.h>

TerminalContext* context;

typedef struct _KB_Context{
    uint8_t counter;
    uint8_t upper;
    uint8_t writeMode;
} KB_Context;

KB_Context kb_context = {
    .counter = 0,
    .writeMode = DATA
};

const char scanCodeCh[] = {
   0, 0, '1', '2', //empty, esc
   '3', '4', '5', '6',
   '7', '8', '9', '0',
   '-', '=', 0, '\t', //backspace
   'q', 'w', 'e', 'r',
   't', 'y', 'u', 'i',
   'o', 'p', '[', ']',
   0,  0, 'a', 's', //enter, lctrl
   'd', 'f', 'g', 'h',
   'j', 'k', 'l', ';',
   '\'', '`', 0, '\\', //lshift
   'z', 'x', 'c', 'v',
   'b', 'n', 'm', ',',
   '.', '/', 0, '*', //rshift
   0, ' ', 0, 0, //lalt, CL, F1
   0, 0, 0, 0, //F2, F3, F4, F5
   0, 0, 0, 0, //F6, F7, F8, F9
   0, 0, 0, '7', //F10, number_lock, scroll_lock
   '8', '9', '-', '4',
   '5', '6', '+', '1',
   '2', '3', 0, '.',
   0, 0, 0, 0, //empty, empty, empty, F11
   0, 0, 0, 0, //F12, empty, empty, empty
   //asd
   0, 0, '1', '2', //empty, esc
   '3', '4', '5', '6',
   '7', '8', '9', '0',
   '-', '=', 0, '\t', //backspace
   'q', 'w', 'e', 'r',
   't', 'y', 'u', 'i',
   'o', 'p', '[', ']',
   0,  0, 'a', 's', //enter, lctrl
   'd', 'f', 'g', 'h',
   'j', 'k', 'l', ';',
   '\'', '`', 0, '\\', //lshift
   'z', 'x', 'c', 'v',
   'b', 'n', 'm', ',',
   '.', '/', 0, '*', //rshift
   0, ' ', 0, 0, //lalt, CL, F1
   0, 0, 0, 0, //F2, F3, F4, F5
   0, 0, 0, 0, //F6, F7, F8, F9
   0, 0, 0, '7', //F10, number_lock, scroll_lock
   '8', '9', '-', '4',
   '5', '6', '+', '1',
   '2', '3', 0, '.',
   0, 0, 0, 0, //empty, empty, empty, F11
   0, 0, 0, 0, //F12, empty, empty, empty
};

char KB_GetChar(uint8_t scanCode)
{
    if(scanCode >= 0x81)
        scanCode -= 0x24;

    return scanCodeCh[scanCode];
}

void KB_Print(uint8_t scanCode)
{
    if(kb_context.counter == 0){

        if(scanCode == 0x01 || scanCode == 0x81){ //esc
            T_TMode(context);
            print(context, "Toggle mode");
            T_NewLine(context);
        }
        else if(scanCode == 0xE0 || scanCode == 0x53){
            T_ClearTerminal(context);
        }
        else if(scanCode == 0x2A || scanCode == 0x36 || scanCode == 0xAA || scanCode == 0xB6){ //shift
            if(kb_context.upper){
                kb_context.upper = 1;
            }
            else{
                kb_context.upper = 1;
            }
        }
        else if(scanCode == 0x1C || scanCode == 0x9C){ //enter
            uint8_t mode = T_GMode(context);
            if (mode == DATA){            
                T_NewLine(context);
            }
            else{
                uint16_t x = 0;
                uint16_t y = 0;
                T_GetCursorPosition(context, &x, &y);
                if(x > 1){ //if no char entered
                    T_TMode(context);
                    CLI_Execute(context);
                    T_TMode(context);
                }
                T_NewLine(context);
            }
        }
        else if(scanCode == 0xE || scanCode == 0x8E){ //backspace
            T_RemoveChar(context);
        }
        else if((scanCode >= 0x3B && scanCode <= 0x44) || (scanCode >= 0x57 && scanCode <= 0x58) ||
                 (scanCode >= 0xBB && scanCode <= 0xC4) || (scanCode >= 0xD7 && scanCode <= 0xD8)){ //F1, F2...

            if(scanCode == 0x3B || scanCode == 0xBB){
                T_StyleTerminal(context, 0x0F);
            }
            if(scanCode == 0x3C || scanCode == 0xBC){
                T_StyleTerminal(context, 0x02);
            }
            if(scanCode == 0x3D || scanCode == 0xBD){
                T_StyleTerminal(context, 0x01);
            }
            if(scanCode == 0x3E || scanCode == 0xBE){
                T_StyleTerminal(context, 0x04);
            }
            if(scanCode == 0x3F || scanCode == 0xBF){
                T_StyleTerminal(context, 0x05);
            }
            if(scanCode == 0x40 || scanCode == 0xC0){
                T_StyleTerminal(context, 0x06);
            }
            if(scanCode == 0x41 || scanCode == 0xC1){
                T_StyleTerminal(context, 0x0E);
            }
            if(scanCode == 0x42 || scanCode == 0xC2){
                T_StyleTerminal(context, 0x0D);
            }
            if(scanCode == 0x43 || scanCode == 0xC3){
                T_StyleTerminal(context, 0x0C);
            }
            if(scanCode == 0x44 || scanCode == 0xC4){
                T_StyleTerminal(context, 0x0B);
            }
            if(scanCode == 0x57 || scanCode == 0xD7){
                T_StyleTerminal(context, 0x03);
            }
            if(scanCode == 0x58 || scanCode == 0xD8){
                T_StyleTerminal(context, 0x01);
            }
        }
        else{
            char ch = KB_GetChar(scanCode);
            
            if (kb_context.upper) //if shift
                if(ch - 32 >= 32)
                    ch -= 32;

            T_PutChar(context, ch);
            kb_context.upper = 0;
        }
        kb_context.counter++;
    }
    else{
        kb_context.counter = 0;
    }
}

void KB_Interrupt(void)
{
    context = Terminal_B8000_8025_GetTerminalContext();

    uint8_t scanCode;
    HAL_PortInByte(0x60, &scanCode);

    KB_Print(scanCode);
}