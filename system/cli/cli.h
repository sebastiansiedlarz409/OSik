#ifndef CLI_H
#define CLI_H

#include "..\terminal\terminal.h"
#include "..\terminal\terminal_B8000_8025.h"

#define CMDS_COUNT 10

typedef uint8_t (*func)(const char*);

void CLI_Execute(TerminalContext* context);
uint8_t CLI_Parse(TerminalContext* context, uint8_t* line);
uint8_t CLI_Info(const char* str);

#endif //PARSER_H