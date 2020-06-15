/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 11 exercise 2
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */

#include <avr/io.h>
#include <stdio.h>
#include "string.h"
#include "io.h"
#include "timer.h"

enum DisplayStates { Start, Display } DisplayState;
const char MSG[] = "CS120B is Legend... wait for it DARY!";
char buffer[] = "                ";
unsigned char pos = 0;
const unsigned char BUFFER_SIZE = 16;
unsigned char msg_size = strlen(MSG);

void TickFct_DisplayMsg()
{
	unsigned char counter = 0;
	switch (DisplayState)
	{
		case Start:
			DisplayState = Display;
			break;
		case Display:
			DisplayState = Display;
			break;
		default:
			DisplayState = Display;
			break;
	}
	
	switch (DisplayState)
	{
		case Start:
			break;
		
		case Display:
			if (!strcmp(buffer, "                ") && pos != 0)
			{
				pos = 0;
			}
			if (pos == 0)
			{
				buffer[BUFFER_SIZE - 1] = MSG[0];
			}
			else if ((pos > 0) && (pos < msg_size))
			{
				for (counter = 1; counter < BUFFER_SIZE; ++counter)
				{
					buffer[counter - 1] = buffer[counter];
				}
				buffer[BUFFER_SIZE - 1] = MSG[pos];
			}
			else
			{
				for (counter = 1; counter < BUFFER_SIZE; ++counter)
				{
					buffer[counter - 1] = buffer[counter];
				}
				buffer[BUFFER_SIZE - 1] = 0x20;
			}
			++pos;
			LCD_DisplayString(1, buffer);
			break;
		}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	TimerSet(200);
	TimerOn();
	
	DisplayState = Start;

	LCD_init();
	LCD_ClearScreen();
	
	while(1)
	{
		TickFct_DisplayMsg();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}