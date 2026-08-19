#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct{
    int width;
    int height;
} Terminal;

int terminalinit(Terminal *terminal);
void terminalRender(Terminal *terminal, char *outbuffer);
void terminaldestroy(Terminal *terminal);

#endif
