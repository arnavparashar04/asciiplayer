#include <stdio.h>
#include <stdint.h>
#include "player.h"
#include "cli.h"       

int main(int argc, char *argv[]){
    cliArgs args = parseArgs(argc, argv);
    if(args.askHelp){
        printf(
            "Usage: avplayer <path> [options]\n"
            "\n"
            "Options:\n"
            "  -h,  --help              Show this help message\n"
            "  -v,  --version           Show version information\n"
            "  -d,  --dirty             Enable dirty updates  (Status : Work In Progress)\n"
            "  -g,  --glyph             Enable glyph matching  (Status : Work In Progress)\n"
            "  -oc, --offcolor          Disable colour output\n"
            "      --fps <number>       Set playback FPS (default: 30)  (Status : Work In Progress)\n"
            "      --width <number>     Set output width (default: 1300)  (Status : Work In Progress)\n"
            "      --height <number>    Set output height (default: 760)  (Status : Work In Progress)\n"
            "\n"
            "Example:\n"
            "  ascii-video video.mp4\n"
        );
        return 0;
    }
    if(args.askVersion){
        printf("Ascii Video Player Version : 0.0.1\n");
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
