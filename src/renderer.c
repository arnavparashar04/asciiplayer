#include "renderer.h"
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALIGNMENT 32

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
int normalize(Renderer *renderer, AVFrame *frame){
    if(renderer->swscontxt == NULL){
        renderer->swscontxt = sws_getContext(renderer->frameWidth, renderer->frameHeight, frame->format, renderer->frameWidth, renderer->frameHeight, AV_PIX_FMT_GRAY8, SWS_BILINEAR, NULL, NULL, NULL);
        if(renderer->swscontxt == NULL){
            return -150; // error map to failed to get context 
        }
        renderer->normframe = av_frame_alloc();
        if(renderer->normframe == NULL){
            return -151; // map to norm frame init failed
        }
        renderer->normframe->format = AV_PIX_FMT_GRAY8;
        renderer->normframe->width = renderer->frameWidth;
        renderer->normframe->height = renderer->frameHeight;
        if(av_frame_get_buffer(renderer->normframe, ALIGNMENT) < 0){
            return -152; //map to norm frame alloc failed
        }
    }
    sws_scale(renderer->swscontxt, (const uint8_t *const *)frame->data, frame->linesize, 0, frame->height, renderer->normframe->data, renderer->normframe->linesize);
    return 0;
}

int render(Renderer *renderer, AVFrame *frame){

}

void rDestroy(Renderer *renderer){
    av_frame_free(&renderer->normframe);
    sws_freeContext(renderer->swscontxt);
    free(renderer->output);
}
