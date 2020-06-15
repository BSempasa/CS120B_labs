/*	Author: Brittiney Sempasa
 *  Partner(s) Name: none
 *	Lab Section: 021
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: 

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,init, inc, dec, zero, zWait, wait} state;

unsigned char button0;
unsigned char button1;
unsigned char tmpC;


int main(void)

{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = start;
	tmpC = 0x07;
	
	while (1)
	{
		
		Tick_shift();
		PORTC = tmpC;
	}
	
	return 0;
}


void Tick_shift(){
	
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;
	
	switch(state){
		// Transitions
		case start:
			state = init;
			break;
		case init:
			if(!button0 && !button1){
				state = init;
			}
			else if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			break;

		case inc:
			state = wait;
			break;
		case dec:
			state = wait;
			break;
		case zero:
		state = zWait;
		break;
		case wait: //forces loop until button removal
		if(button0 && !button1){
			state = wait;
		}
		else if(!button0 && button1){
			state = wait;
		}
		else if(button0 && button1){
			state = zero;
		}
		else{
			state = init;
		}
		break;
		case zWait: //wait loop for zero state
		if(button0 && button1){
			state = zWait;
		}
		else{
			state = wait;
		}
		default:
		break;
	}

	switch(state){
		// State actions
		case start:
		break;
		case init:
		break;
		case inc:
		if (tmpC < 32){
			tmpC << 1;
		}
		break;
		case dec:
		if (tmpC > 1){
			tmpC= >> 1;
		}
		break;
		case zero:
		tmpC = 0x00;
		break;
		case wait:
		break;
		case zWait:
		break;
		default:
		break;
	}

}