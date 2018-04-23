#ifndef __MECHANISM__
#define __MECHANISM__

#include "map.h"

void init_game(struct struct_game *game);
void draw_game(struct struct_game *game);
void step_game(struct struct_game *game);
void move_hero_up(struct struct_game *game);
void move_hero_down(struct struct_game *game);
#endif
