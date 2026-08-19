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
   renderer->targetWidth = frameWidth;
   renderer->targetHeight = frameHeight; //upto v1 frame res = target res
   renderer->charCellWidth = 5;
   renderer->charCellHeight = 10;
   renderer->charMap = ".`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
   renderer->charMapLen = strlen(renderer->charMap);
   renderer->swscontxt = NULL;
   renderer->normframe = NULL;
   int outputWidth = renderer->frameWidth + renderer->charCellWidth - 1/ renderer->charCellWidth;
   int outputHeight = renderer->frameHeight + renderer->charCellHeight - 1 / renderer->charCellHeight;
   renderer->output = malloc(outputHeight * (outputWidth + 1) + 1);
   if (renderer->output == NULL) {
         return -153; //map to output allocation failed
    }
   return 0;
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

char *render(Renderer *renderer, AVFrame *frame){
    if(normalize(renderer,frame)<0){
        return NULL;
    }
    AVFrame *norm = renderer->normframe;
    int outputIndex = 0;
    for(int j = 0; j<renderer->frameHeight; j+=renderer->charCellHeight){
        for(int i = 0; i<renderer->frameWidth; i+= renderer->charCellWidth){
            int sum = 0;
            int endX = i + renderer->charCellWidth;
            if (endX > renderer->frameWidth){
                endX = renderer->frameWidth;
            }    
            int endY = j + renderer->charCellHeight;
            if (endY > renderer->frameHeight){
                  endY = renderer->frameHeight;
            }      
            int cellWidth = endX - i;
            int cellHeight = endY - j;

            for(int n = j; n< endY; n++){
                for(int m = i; m < endX; m++){
                    sum += norm->data[0][n * norm->linesize[0] + m]; 
                }
            }

            sum = sum/(cellHeight*cellWidth);
            int index = sum * renderer->charMapLen / 256;
            renderer->output[outputIndex++] = renderer->charMap[index];
        }
        renderer->output[outputIndex++] = '\n';
    }
    renderer->output[outputIndex] = '\0';
    return renderer->output;
}

void rDestroy(Renderer *renderer){
    av_frame_free(&renderer->normframe);
    sws_freeContext(renderer->swscontxt);
    renderer->swscontxt = NULL;
    free(renderer->output);
    renderer->output=NULL;
}
