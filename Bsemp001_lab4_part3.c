/*	Author: Brittiney Sempasa
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{locked, wait, release, unlock} state;



unsigned char buttonX;

unsigned char buttonY;

unsigned char buttonP;

unsigned char buttonLock;



unsigned char tmpB;





void lock_Tick(){

	buttonX = PINA & 0x01;

	buttonY = PINA & 0x02;

	buttonP = PINA & 0x04;

	buttonLock = PINA & 0x80;

	

	switch(state){ // Transitions

		case locked:
			if(buttonLock){
				state = locked;
			}
			if(!buttonX && !buttonY && buttonP && !buttonLock){
				state = wait;
			}
			else{
				state = locked;
			}
			break;
		case wait:
		if(!buttonX && !buttonY && buttonP && !buttonLock){
			state = wait;
		}
		else if(!buttonX && !buttonY && !buttonP && !buttonLock){
			state = release;
		}
		else{
			state = locked;
		}
		break;
		case release:
		if(!buttonX && !buttonY && !buttonP && !buttonLock){
			state = release;
		}
		else if(!buttonX && buttonY && !buttonP && !buttonLock){
			state = unlock;
		}

		else{

			state = locked;

		}

		break;

		case unlock:

		if(!buttonX && !buttonY && !buttonP && buttonLock){

			state = locked;

		}

		else{

			state = unlock;

		}

		break;

	}

	switch(state){ // State actions

		case locked:

		tmpB = 0x00;

		break;

		case wait:

		break;

		case release:

		break;

		case unlock:

		tmpB = 0x01;

		break;

	}

}



int main(void)

{

	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs

	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs

	// initialize to 0s

	

	state = locked;



	while (1)

	{

		lock_Tick();

		PORTB = tmpB;



	}



	return 0;

}
