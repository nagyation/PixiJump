
#include "DIO.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "mechanism.h"
#include "map.h"
#include "character.h"
#include <stdlib.h>
#include <util/delay.h>

struct struct_game *game ;
volatile int speed = 0x86 ;
volatile int level = 10;
volatile int last_step = 0;

void game_logic(){

	if(game->step - last_step >= level)
	{
		add_character(game, MONSTER, ((rand() + level + game->step)%2), 15);
		last_step = game->step;
	}
	
	if(game->step%20 == 0)
		level -= 1;
		if(level ==  3)
			level = 10 ;

}

int main()
{
	game = malloc(sizeof(struct struct_game));

	init_map(game);
    init_game(game) ;

    add_character(game, HERO, 0, 0);


    DIO_InitPortDirection(PC, INPUT, 0x03);
    DIO_WritePort(PC, HIGH, 0x03);



	TCNT1H = speed ;
	TCNT1L = 0x00 ;
	TCCR1A = 0x00 ;
    TCCR1B = 0x02 ;

    TIMSK = (1<<TOIE1);
    sei();



	while(1){
		draw_game(game);
		while (game->game_state == GAME_START){
//			cli();
			if(DIO_ReadPort(PC, 0x03) == 0)
				game->game_state = GAME_RUN;
//			sei();
		}
		
		if (game->game_state == GAME_ENDED){
//			cli();
			while(DIO_ReadPort(PC, 0x03) != 0)
				game->game_state = GAME_START;
//			sei();
		}

		if(DIO_ReadPort(PC, 0x01) == 0){
			move_hero_up(game);
//			DIO_WritePort(PC, HIGH,0x04);
		}
		if(DIO_ReadPort(PC, 0x02) == 0)
			move_hero_down(game);
	}
}



ISR(TIMER1_OVF_vect){
	step_game(game);
	game_logic();
	if(game->step%5 == 0)
		speed++;
	if(speed == 0xFF)
		game->game_state = GAME_WON;
	TCNT1H = speed ;
	TCNT1L = 0xEE ;
}





