#include "player.h"
#include "fetcher.h"
#include "decoder.h"
#include "renderer.h"
#include "terminal.h"
#include "audio.h"
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>

int playerinit(Player *player, const char *path){
    int retrned = fetcherInit(player->fetcher,path);
    if(retrned != 0){
        return -50; //todo : here in error enum map to critical fetcher failure
    }
    retrned = decoderInit(player->decoder,player->fetcher);
    if(retrned!=0){
        return -51; //todo :here in error enum map to critical decoder failure
    }
   
    retrned = rendererinit(player->renderer);
    if(retrned !=0){
        return -52; //todo: in error enum map to critical renderer failure
    }

}

int playerPlay(Player *player){
   AVPacket *packet = av_packet_alloc();
   AVFrame *frame = av_frame_alloc();

   if(packet == NULL || frame == NULL){
       av_packet_free(&packet);
       av_frame_free(&frame);
   }

   while(fetcherNextPacket(&player->fetcher, packet) >= 0){
       if(packet->stream_index != player->fetcher.vStreamIndex){
           av_packet_unref(packet);
       }
       int rtrned = avcodec_send_packet(player->decoder.codecContext, packet); //here it is actually sent to the decoder with codec context so decoder will know how it should decode                                                   
       av_packet_unref(packet);
       if(rtrned <0){
           return -100; //todo: map in error enum to criticl decoder error
       }

   }

   av_packet_free(&packet);
   av_frame_free(&frame);
}





