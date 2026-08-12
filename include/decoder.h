#ifndef DECODER_H
#define DECODER_H

#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>

#include "fetcher.h"
typedef struct{
    const AVCodec *codec;
    AVCodecContext *codecContext;
} Decoder;

int decoderInit(Decoder *decoder, Fetcher *fetcher);

void decoderDestroy(Decoder *decoder);

#endif