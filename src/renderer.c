#include "renderer.h"
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
#include <stdlib.h>
#include <string.h>

int rendererinit(Renderer *renderer, int frameWidth, int frameHeight){
   renderer->frameWidth = frameWidth;
   renderer->frameHeight = frameHeight;
   renderer->targetWidth = frameHeight;
   renderer->targetHeight = frameHeight; //upto v1 frame res = target res
   renderer->charCellWidth = 5;
   renderer->charCellHeight = 10;

   renderer->charMap = ".`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
   renderer->charMapLen = strlen(renderer->charMap);
   renderer->swscontxt = NULL;
   renderer->normframe = NULL;
   renderer->output = NULL;
}

int rendererComp(Renderer *renderer){

}

int normalize(Renderer *renderer, AVFrame *frame){

}

int render(Renderer *renderer, AVFrame *frame){

}

void rDestroy(Renderer *renderer){
    av_frame_free(&renderer->normframe);
    sws_freeContext(renderer->swscontxt);
    free(renderer->output);
}
