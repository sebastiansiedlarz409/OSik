#include "..\common.h"
#include "..\libs\string.h"
#include "..\libs\heap.h"
#include "cli.h"
#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

char* cmds[CMDS_COUNT] = {
    "info",
};

func cmds_handlers[CMDS_COUNT] = {
    CLI_Info,
};

void CLI_Execute(TerminalContext* context){
    uint8_t* line = NULL;
    uint8_t cmd = CLI_Parse(context, line);
    uint8_t result = cmds_handlers[cmd]((char*)line);
    if(result != 1){
        print(context, "\n\rSomething went wrong!");
    }
}

uint8_t CLI_Parse(TerminalContext* context, uint8_t* line){
    //get current position
    uint16_t x = 0;
    uint16_t y = 0;
    T_GetCursorPosition(context, &x,&y);

    uint16_t size = x;

    line = HEAP_Malloc(size);

    for(int i = size-1;i>=0;i--){
        line[i] = T_GetChar(context);
        x--;
        T_SetCursorPosition(context, x, y);
    }
    line[size-1] = '\0';

    T_NewLine(context);

    for(uint16_t i = 0;i<CMDS_COUNT;i++){
        if(STR_CMP((char*)line, cmds[i])){
            return i;
        }
    }

    HEAP_Free(line);

    return 0;
}

uint8_t CLI_Info(const char* str){
    UNUSED(str);
    TerminalContext* context = Terminal_B8000_8025_GetTerminalContext();
    print(context, "Osik\n\rBy Sebastian Siedlarz");

    return 1;
}