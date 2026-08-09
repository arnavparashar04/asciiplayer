#ifndef CLI_H
#define CLI_H
#define PATH_MAX 512

#include <stdbool.h>

typedef struct cliArgs{
    char path[PATH_MAX];
    int fps;
    float width;
    float height;
    bool vid;
    bool colour;
    bool glyphMatch;
    bool dirtyUpdate;
    bool askHelp;
    bool askVersion;
} cliArgs;

cliArgs init_cliargs(void);
cliArgs parseArgs(int argn, char **args);

#endif