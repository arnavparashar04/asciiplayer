#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "audio.h"
#include "decoder.h"
#include "fetcher.h"
#include "player.h"
#include "renderer.h"
#include "terminal.h"
#include "cli.h"
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>       
#include <libavutil/avutil.h>         
#include <libavutil/frame.h>         
#include <libavutil/error.h>          
#include <libswscale/swscale.h>       

int main(int argc, char *argv[]){
    cliArgs args = parseArgs(argc, argv);
    if(args.askHelp){
        printf(
            "Usage: avplayer <path> [options]\n"
            "\n"
            "Options:\n"
            "  -h,  --help              Show this help message\n"
            "  -v,  --version           Show version information\n"
            "  -d,  --dirty             Enable dirty updates\n"
            "  -g,  --glyph             Enable glyph matching\n"
            "  -oc, --offcolor          Disable colour output\n"
            "      --fps <number>       Set playback FPS (default: 30)\n"
            "      --width <number>     Set output width (default: 1300)\n"
            "      --height <number>    Set output height (default: 760)\n"
            "\n"
            "Example:\n"
            "  ascii-video video.mp4 --fps 60 --width 1920 --height 1080\n"
        );
        return 0;
    }
    if(args.askVersion){
        printf("Ascii Video Player Version : 0.0.1\n");
        return 0;

    }
    
}