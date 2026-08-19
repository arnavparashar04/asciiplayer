#ifndef FETCHER_H
#define FETCHER_H

#include <libavformat/avformat.h>

typedef struct{
    AVFormatContext *frmtcontext;
    int vStreamIndex;
    int aStreamIndex;
} Fetcher;

int fetcherInit(Fetcher *fetcher, const char *path);
int fetcherNextPacket(Fetcher *fetcher, AVPacket *packet);
void fetcherDestroy(Fetcher *fetcher);

#endif
