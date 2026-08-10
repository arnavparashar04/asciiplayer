#ifndef FETCHER_H
#define FETCHER_H

#include <libavformat/avformat.h>

typedef struct{
    AVFormatContext *frmtcontext;
    int vStreamIndex;
    int aStreamIndex;
} Fetcher;

int fetcherInit(Fetcher *fetcher, char *path);
int fetcherNextPacket();
int fetcherDefer();

#endif