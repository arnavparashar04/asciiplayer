#include "cli.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

cliArgs init_cliargs() {
    return (cliArgs){
        .path = "",
        .fps = 30,
        .width = 1300,
        .height = 760,
        .colour = true,
        .glyphMatch = false,
        .dirtyUpdate = false,
        .askHelp = false,
        .askVersion = false
    };
}

cliArgs parseArgs(int argn, char **args) {
    cliArgs argS = init_cliargs();
    bool flagOptions = false;
        for (int i = 1; i < argn; i++) {
        if (strcmp("--help", args[i]) == 0 || strcmp("-h", args[i]) == 0) {
            argS.askHelp = true;
            flagOptions = true;
        }
        if (strcmp("--version", args[i]) == 0 || strcmp("-v", args[i]) == 0) {
            argS.askVersion = true;
            flagOptions = true;
        }
        if (strcmp("--dirty", args[i]) == 0 || strcmp("-d", args[i]) == 0) {
            argS.dirtyUpdate = true;
            flagOptions = true;
        }
        if (strcmp("--glyph", args[i]) == 0 || strcmp("-g", args[i]) == 0) {
            argS.glyphMatch = true;
            flagOptions = true;
        }
        if (strcmp("--offcolor", args[i]) == 0 || strcmp("-oc", args[i]) == 0) {
            argS.colour = false;
            flagOptions = true;
        }
        if (strcmp("--fps", args[i]) == 0) {
            flagOptions = true;
            if (i + 1 < argn) {
                argS.fps = (int)strtol(args[++i], NULL, 10);
            }
        }
        if (strcmp("--width", args[i]) == 0) {
            if (i + 1 < argn) {
                argS.width = (int)strtol(args[++i], NULL, 10);
            }
        }
        if (strcmp("--height", args[i]) == 0) {
            flagOptions = true;
            if (i + 1 < argn) {
                argS.height = (int)strtol(args[++i], NULL, 10);
            }
        }
    }
    if(argn>1){
        if(access(args[1], F_OK) == 0){
            strcpy(argS.path, args[1]);
        }
        else{
            if (flagOptions == false){
            printf("Incorrect path\nExiting\n");
            exit(10);
            }
        }
    }

    return argS;
}
