#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

static char scanCodeCh[] = {
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

void KB_Interrupt(void);

#endif //KEYBOARD_H