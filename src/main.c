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
    cliArgs args = init_cli_args();
}