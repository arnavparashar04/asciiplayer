#include "player.h"
#include "fetcher.h"
#include "decoder.h"
#include "renderer.h"
#include "terminal.h"
#include "audio.h"
#include <asm-generic/errno-base.h>
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>
#include <time.h>
static long long getTimeNs(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int playerinit(Player *player, const char *path){
    int retrned = fetcherInit(&player->fetcher,path);
    AVStream *stream = player->fetcher.frmtcontext->streams[player->fetcher.vStreamIndex];
    if(retrned != 0){
        return -50; //todo : here in error enum map to critical fetcher failure
    }
    retrned = decoderInit(&player->decoder,&player->fetcher);
    if(retrned!=0){
        return -51; //todo :here in error enum map to critical decoder failure
    }
   
    retrned = rendererinit(&player->renderer, stream->codecpar->width, stream->codecpar->height);
    if(retrned !=0){
        return -52; //todo: in error enum map to critical renderer failure
    }
    player->output = NULL;
    player->frameTime =1000000000LL * stream->avg_frame_rate.den /stream->avg_frame_rate.num;
    terminalinit(&player->terminal);
    return 0;
}

int playerPlay(Player *player){
   AVPacket *packet = av_packet_alloc();
   AVFrame *frame = av_frame_alloc();

   if(packet == NULL || frame == NULL){
       av_packet_free(&packet);
       av_frame_free(&frame);
   }
   long long lastDisplay = getTimeNs();
   while(fetcherNextPacket(&player->fetcher, packet) >= 0){
       if(packet->stream_index != player->fetcher.vStreamIndex){
           av_packet_unref(packet);
           continue;
       }
       int rtrned = avcodec_send_packet(player->decoder.codecContext, packet);                                                   
       av_packet_unref(packet);
       if(rtrned <0){
           return -100; //todo: map in error enum to criticl decoder failure
       }

       while(1){
           //this loop may need to modified for play/pause operations
           rtrned = avcodec_receive_frame(player->decoder.codecContext,frame);
           if(rtrned == AVERROR(EAGAIN)|| rtrned == AVERROR_EOF || rtrned == AVERROR_EXIT){
               break;
           }
           if(rtrned < 0 ){
               av_frame_free(&frame);
               av_packet_free(&packet);

               return -101; // todo: map to critcial player failure
           }

           player->output = render(&player->renderer,frame);
           if(player->output == NULL){
               return -200; //critical renderer failure
           }

           long long now = getTimeNs();
           long long elapsed = now - lastDisplay;
           long long remaining = player->frameTime - elapsed;
           if(remaining > 0){
               struct timespec sleepTime = {
                   .tv_sec = remaining / 1000000000LL,
                   .tv_nsec = remaining % 1000000000LL
               };
               nanosleep(&sleepTime, NULL);
           }
           terminalRender(player->output);
           lastDisplay = getTimeNs();
       }
   }
    
   av_packet_free(&packet);
   av_frame_free(&frame);
   playerDestroy(player);
   return 0;
}

void playerDestroy(Player *player){
    terminaldestroy(&player->terminal);
    rDestroy(&player->renderer);
    decoderDestroy(&player->decoder);
    fetcherDestroy(&player->fetcher);
}