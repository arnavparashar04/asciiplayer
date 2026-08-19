#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct{
    int initialized; //in later versions terminal will request terminal emulator for resize so this will be modified
} Terminal;

void terminalinit(Terminal *terminal);
void terminalRender(const char *output);
void terminaldestroy(Terminal *terminal);

#endif
