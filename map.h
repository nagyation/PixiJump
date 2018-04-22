#ifndef __MAP__
#define __MAP__

#include "character.h"

#define GAME_PAUSE  0
#define GAME_RUN 1
#define GAME_START 2
#define GAME_ENDED 3

#define MAP_COLS 16
#define MAP_ROWS 2

struct struct_game{

    struct struct_character map[MAP_ROWS][MAP_COLS];
    char monsters_number;
    char game_state;
    int score;
};



#endif
