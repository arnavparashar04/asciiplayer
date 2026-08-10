#include <libavformat/avformat.h>
#include <fetcher.h>
#include<string.h>

int fetcherInit(Fetcher *fetcher, char *path){
    fetcher->frmtcontext = NULL;
    fetcher->vStreamIndex = -1;
    fetcher->aStreamIndex = -1;

    int cont = avformat_open_input(&fetcher->frmtcontext, path, NULL, NULL);//status code var, if fails then wrong path/unsupported format
    if(cont <0){
        return -2;
    }

    cont = avformat_find_stream_info(fetcher->frmtcontext, NULL); //now frmtcontext pointer getss filled with context data on the file liek stream codec etc
    if(cont <0){
        return -3;
    }

    for(unsigned int i = 0; i< fetcher->frmtcontext->nb_streams ; i++){ //rn upto version 1.0.0 support only 1 video stream and 1 audio stream, later versions could potentially support more streams
        AVStream *stream = fetcher->frmtcontext->streams[i];
        if(stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            if(fetcher->vStreamIndex == -1){
            fetcher->vStreamIndex = i;
            }
        }
        else if(stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
            if(fetcher->aStreamIndex == -1){
            fetcher->aStreamIndex = i;
            }
        } 
    }
    if(fetcher->vStreamIndex == -1){
        return -4;
    }

    return 0;
}

int fetcherNextPacket(Fetcher *fetcher, AVPacket *packet){ //like before the packet pointer is the one modified here, function returns a status code for pass or fail
    return av_read_frame(fetcher->frmtcontext, packet);
}


void fetcherDestroy(Fetcher *fetcher)
{
    avformat_close_input(&fetcher->frmtcontext); //free mem kinda
}