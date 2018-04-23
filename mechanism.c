#include "mechanism.h"
#include "map.h"
#include "lcd.h"


void init_game(struct struct_game *game)
{
    LCD_init();
    game->score =0;
    game->game_state = GAME_START;
    game->monsters_number = 0;
}

void display_game_over()
{
    LCD_display_string((unsigned char *) "Game Over");
}

void display_game_start()
{
    LCD_display_string((unsigned char *) "Game Start");
}

void display_game_pause()
{
    LCD_display_string((unsigned char *) "Game Paused");
}

void draw_game(struct struct_game *game)
{
    int x,y;
    
    switch(game->game_state)
    {
    case GAME_PAUSE:
	display_game_pause();
	break;
    case GAME_START:
	display_game_start();
	break;
    case GAME_ENDED:
	display_game_over();
    case GAME_RUN:
	for( x = 0; x < MAP_ROWS ; x ++)
	    for(y =0; y < MAP_COLS ; y++)
	    {
		LCD_gotoxy(x,y);
		LCD_display_string(&game->map[x][y].shape) ;
	    }
	break;
	
    }
	
    
    
}



void step_game(struct struct_game *game)
{

    int x,y;

    if((game->map[0][0].shape == HERO
       &&
       game->map[0][1].shape == MONSTER)
       ||
       (game->map[1][0].shape == HERO
       &&
	game->map[1][1].shape == MONSTER)
	)
	
    {
	
	game->game_state = GAME_ENDED;
	display_game_over();
	return;
    }
       
    for( x = 0; x < MAP_ROWS ; x ++)
	for(y =1; y < MAP_COLS ; y++)
	{
	    game->map[x][y-1] =  game->map[x][y];
	}

    game->score += game->monsters_number;

}
