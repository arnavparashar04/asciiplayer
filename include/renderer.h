#ifndef RENDERER_H
#define RENDERER_H

#include <libavutil/frame.h>

typedef struct {
    //src res 
    int frameWidth;
    int frameHeight;
    //target res 
    int targetWidth;
    int targetHeight;

    int charCellWidth;
    int CharCellHeight;

    const char *charMap;
    int charMapLen;
    struct SwsContext *swscont;
    AVFrame *frame;
    char *output;
} Renderer;

int rendererinit(Renderer *renderer);
int rendererComp(Renderer *renderer);
int normalize(Renderer *renderer, AVFrame *frame);
int render(Renderer *renderer, AVFrame *frame);
void rDestroy(Renderer *renderer);

#endif
