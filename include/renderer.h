#ifndef RENDERER_H
#define RENDERER_H

#include <libavutil/frame.h>
#include <libswscale/swscale.h>

typedef struct {
    //src res 
    int frameWidth;
    int frameHeight;
    //target res 
    int targetWidth;
    int targetHeight;

    int charCellWidth;
    int charCellHeight;

    const char *charMap;
    int charMapLen;
    char *output;
    struct SwsContext *swscontxt;
    AVFrame *normframe;
} Renderer;

int rendererinit(Renderer *renderer, int frameWidth, int frameHeight);
int normalize(Renderer *renderer, AVFrame *frame);
int render(Renderer *renderer, AVFrame *frame);
void rDestroy(Renderer *renderer);

#endif
