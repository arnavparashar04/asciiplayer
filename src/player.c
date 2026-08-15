#include "player.h"
#include "fetcher.h"
#include "decoder.h"
#include "renderer.h"
#include "terminal.h"
#include "audio.h"
#include <libavcodec/avcodec.h>

int playerinit(Player *player, const char *path){
    int retrned = fetcherInit(player->fetcher,path);
    if(retrned != 0){
        return -50; //here in error enum map to critical fetcher failure
    }
    retrned = decoderInit(player->decoder,player->fetcher);
    if(retrned!=0){
        return -51; //here in error enum map to critical decoder failure
    }
   
    retrned = rendererinit(player->renderer);
    if(retrned !=0){
        return -52; //in error enum map to critical renderer failure
    }

}
