#ifndef PLAYER_H
#define PLAYER_H

#include"fetcher.h"
#include "decoder.h"
#include "renderer.h"
#include "terminal.h"
#include "audio.h"


typedef struct{

    Fetcher fetcher;
    Decoder decoder;
    Renderer renderer;
    Terminal terminal;
    Audio audio;
    char *output;
}Player;

int playerinit(Player *player, const char *path);
int playerPlay(Player *player);
void playerDestroy(Player *player);

#endif
