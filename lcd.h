/*
 *  Author: pixels
 *
 *  LCD.h
 *	This driver is for --> Hitachi HD44780 LCD 16x2 <--
 *
 *  This driver is for LCD to run in 4-bit mood on a single port
 *  
 *  NOTE :: This driver needs a DIO driver in order to run 
 *  
 *  NOTE :: This driver uses delay, so that the LCD has time to finish its process
 * 
 */ 

#ifndef _LCD_H_
#define _LCD_H_ 

#define F_CPU 8000000  


#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>


#define LCD_PORT  PD
#define LCD_RS    0		// register select
#define LCD_RW    1		// read/write pin
#define LCD_EN    2		// enable pin 
#define DATA_MASK 0xF0  // data pins 

	
void LCD_init();  // initialize LCD

void LCD_gotoxy(uint8_t x, uint8_t y);

void LCD_write_char(uint8_t character);

void LCD_display_string( char* str);	// print strings

void LCD_clear_display();	

void LCD_display_int(int decimal) ;


#endif
