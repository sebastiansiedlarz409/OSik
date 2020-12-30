#include "logo.h"
#include "terminal/terminal.h"
#include "terminal/terminal_B8000_8025.h"

TerminalContext* context;

void LOGO_ShowLogo(void)
{
    context = Terminal_B8000_8025_GetTerminalContext();

    T_StyleTerminal(context, 0x0C);

    print(context, "########                  #                     \r\n");
    print(context, "#      #                  #                     \r\n");
    print(context, "#      #              #   #                     \r\n");
    print(context, "#      #                  #                     \r\n");
    print(context, "#      #   ########   #   #    ##               \r\n");
    print(context, "#      #   #          #   #  ##                 \r\n");
    print(context, "#      #   ####       #   ###                   \r\n");
    print(context, "#      #       ####   #   ###                   \r\n");
    print(context, "#      #          #   #   #  ##                 \r\n");
    print(context, "########   ########   #   #    ##               \r\n\r\n");

    T_StyleTerminal(context, 0x02);

}

void LOGO_ShowDieLogo(void)
{
    context = Terminal_B8000_8025_GetTerminalContext();

    T_StyleTerminal(context, 0x14);

    print(context, "########                  #               #        #     #        #          \r\n");
    print(context, "#      #                  #                 #    #         #    #            \r\n");
    print(context, "#      #              #   #                    #              #              \r\n");
    print(context, "#      #                  #                  #   #          #   #            \r\n");
    print(context, "#      #   ########   #   #    ##         #        #     #        #          \r\n");
    print(context, "#      #   #          #   #  ##                                              \r\n");
    print(context, "#      #   ####       #   ###             #########################          \r\n");
    print(context, "#      #       ####   #   ###            #                #    #   #          \r\n");
    print(context, "#      #          #   #   #  ##                           #    #             \r\n");
    print(context, "########   ########   #   #    ##                          ####              \r\n\r\n");

    T_StyleTerminal(context, 0x17);

}