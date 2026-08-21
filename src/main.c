#include <stdio.h>
#include <stdint.h>
#include "player.h"
#include "cli.h"       

int main(int argc, char *argv[]){
    cliArgs args = parseArgs(argc, argv);
    if(args.askHelp){
        printf(
            "Usage:  asciiplayer <path> or <options>\n"
            "\n"
            "Options:\n"
            "  -h,  --help              Show this help message\n"
            "  -v,  --version           Show version information\n"
            );
        return 0;
    }
    if(args.askVersion){
        printf("Ascii Video Player Version : 1.0.0\n");
        printf("github.com/arnavparashar04\n");
        return 0;

    }

    Player player;
    int rtrned = playerinit(&player, args.path);
    if(rtrned != 0){
        return rtrned;
    }
    rtrned = playerPlay(&player);
    return rtrned;

}
