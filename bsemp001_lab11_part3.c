/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 11 exercise 3
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include <stdio.h>
#include "io.h"
#include "keypad.h"
#include "scheduler.h"

unsigned char tmpB = 0x00;

enum SM1_States{SM1_output};

int SMTick1(int state){
	
	unsigned char x;
	x = GetKeypadKey();
	
	switch(state){
		case SM1_output:
		switch (x) {
			case '\0': 
				break; // All 5 LEDs on
			case '1': 
				tmpB = 0x01;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break; 
			case '2': 
				tmpB = 0x02;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '3': 
				tmpB = 0x03;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '4': 
				tmpB = 0x04;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '5': 
				tmpB = 0x05;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '6': 
				tmpB = 0x06;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '7': 
				tmpB = 0x07;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '8': 
				tmpB = 0x08;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '9': 
				tmpB = 0x09;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case 'A': 
				tmpB = 0x0A;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x37); 
				break;
			case 'B': 
				tmpB = 0x0B;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x37); 
				break;
			case 'C': 
				tmpB = 0x0C;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x37); 
				break;
			case 'D': 
				tmpB = 0x0D;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x37); 
				break;
			case '*': 
				tmpB = 0x0E;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x1C); 
				break;
			case '0': 
				tmpB = 0x00;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + '0'); 
				break;
			case '#': 
				tmpB = 0x0F;
				LCD_Cursor(1); 
				LCD_WriteData(tmpB + 0x14); 
				break;
			default: 
				tmpB = 0x1B; 
				break; 
		}
		state = SM1_output;
		PORTD=tmpB;
		break;
	}
	return state;
}


int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; 
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long int SMTick1_calc = 50;

	unsigned long int tmpGCD = 1;

	unsigned long int GCD = tmpGCD;

	unsigned long int SMTick1_period = SMTick1_calc;

	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = 0;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &SMTick1;

	TimerSet(GCD);
	TimerOn();
	LCD_init();

	unsigned short i;
	while(1) {
		for ( i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}