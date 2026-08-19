#include "terminal.h"
#include <stdio.h>

void terminalinit(Terminal *terminal){
    terminal->initialized = 1;
    printf("\033[2J");   
    printf("\033[H");   
    printf("\033[?25l");    
}

void terminalRender(const char *output){
    printf("\033[H");
    fputs(output, stdout);
    fflush(stdout);
}

void terminaldestroy(Terminal *terminal){
    terminal->initialized = 0;
    printf("\033[?25h"); 
    fflush(stdout);
}
