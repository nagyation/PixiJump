#include "mechanism.h"
#include "map.h"
#include "lcd.h"
#include <stdlib.h>

void init_game(struct struct_game *game)
{
    LCD_init();
    game->score =0;
    game->game_state = GAME_START;
    game->monsters_number = 0;
}

void display_game_over(struct struct_game *game)
{
	LCD_gotoxy(1,1);
    LCD_display_string("Game Over");
    _delay_us(1000);

/*
  LCD_gotoxy(1,1);
    LCD_display_string("SCORE IS: ");
    _delay_ms(100);
*/}

void display_game_start()
{
	LCD_gotoxy(1,1);
    LCD_display_string("Game Start");
}

void display_game_won()
{
	LCD_gotoxy(1,1);
    LCD_display_string("You Win!!!!!!");
}

void display_game_pause()
{
	LCD_gotoxy(1,1);
    LCD_display_string("Game Paused");
}

void draw_game(struct struct_game *game)
{
    int x,y;
    LCD_gotoxy(1,1);
    switch(game->game_state)
    {
    case GAME_PAUSE:
	display_game_pause();
	break;
    case GAME_START:
	display_game_start();
	break;
    case GAME_ENDED:
	display_game_over(game);
	break;
	case GAME_WON:
	display_game_won();
	break;
	case GAME_RUN:
	for( x = 0; x < MAP_ROWS ; x ++)
	    for(y =0; y < MAP_COLS ; y++)
	    {
	    LCD_gotoxy(y+1,x+1);
		LCD_write_char(game->map[x][y].shape) ;
	    }
	break;
	
    }
	
    
    
}



void step_game(struct struct_game *game)
{


	if(game->game_state != GAME_RUN)
		return;
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

	display_game_over(game);
	return;
    }
       
    for( x = 0; x < MAP_ROWS ; x ++)
	for(y =0; y < MAP_COLS ; y++)
	{	
		if(game->map[x][y-1].shape == HERO || game->map[x][y].shape == HERO)
			continue;
		if(y == 0 && game->map[x][y].shape == MONSTER)
		{
			game->monsters_number -= 1;
			game->score += 1;
			game->map[x][y].shape = EMPTY;
			continue;
		}
	    game->map[x][y-1] =  game->map[x][y];
	    game->map[x][y].shape = EMPTY;
	}

    
    game->step += 1;
}

void move_hero_up(struct struct_game *game)
{
	int loc = game->hero_loc;
	game->map[loc][0].shape = EMPTY;
	game->map[1][0].shape = HERO;
	game->hero_loc = 1;
}
void move_hero_down(struct struct_game *game){

	int loc = game->hero_loc;
	game->map[loc][0].shape = EMPTY;
	game->map[0][0].shape = HERO;
	game->hero_loc = 0;
}