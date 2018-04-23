#include "map.h"


void init_map(struct struct_game *game)
{
    int x,y;
    for(x =0; x < MAP_ROWS ; x ++)
	for(y = 0 ; y < MAP_COLS ; y ++)
	{
	    game->map[x][y].shape = EMPTY;
	}
}
void add_character(struct struct_game *game, char character, char x, char y)
{
    game->map[x][y].shape = character;
}
