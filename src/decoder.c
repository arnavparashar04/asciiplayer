#include "decoder.h"
#include "fetcher.h"
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>

int decoderInit(Decoder *decoder, Fetcher *fetcher){
    decoder->codec = NULL;
    decoder->codecContext = NULL;
    AVStream *stream = fetcher->frmtcontext->streams[fetcher->vStreamIndex];
    AVCodecParameters *codecpar = stream->codecpar;
    decoder->codec = avcodec_find_decoder(codecpar->codec_id);
    if (decoder->codec == NULL) {
        return -5; //btw this type of error handling will be changed in future, ik it is shit rn but there are more imporant things that need to be impleemnted rather than a proper error handling suite rn
    }

    decoder->codecContext = avcodec_alloc_context3(decoder->codec);

    if (decoder->codecContext == NULL) {
        return -6;
    } 
    int ret = avcodec_parameters_to_context(decoder->codecContext,codecpar);
    if (ret < 0) {
        avcodec_free_context(&decoder->codecContext);
        return -7;
    }

    ret = avcodec_open2(decoder->codecContext,decoder->codec,NULL);

    if (ret < 0) {
        avcodec_free_context(&decoder->codecContext);
        return -8; //TODO: move to a better error handling way smth like enum with all error codes instead, rather than using magic numbers like rn
    }

    return 0;

}

void decoderDestroy(Decoder *decoder){
    avcodec_free_context(&decoder->codecContext);
}