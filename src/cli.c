#include "cli.h"
#include <string.h>

cliArgs init_cliargs(){
    return (cliArgs){
    .path = "",
    .fps = 30,
    .width = 1300,
    .height = 760,
    .vid = false,
    .colour = false,
    .glyphMatch = false,
    .dirtyUpdate = false,
    .askHelp = false,
    .askVersion = false
    };
}