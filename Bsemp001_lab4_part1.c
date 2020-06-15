/*	Author: Brittiney Sempasa
 *  Partner(s) Name: none
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is
                          initially on. Pressing a button connected to PA0 turns
                          off PB0's LED and turns on PB1's LED, staying that way
                          after button release. Pressing the button again turns
                          off PB1's LED and turns on PB0's LED.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, led2, wait, led1} state;



unsigned char button;

unsigned char tmpB;





void led_Tick(){

	switch(state){

		case init:
			if(button == 1){
				state = led2;
			}
			else{
				state = init;
			}
			break;

		case led2:
			if(button == 1){
				state = led2;
			}
			else{
				state = wait;
			}
			break;
		case wait:
			if(button == 1){
			state = led1;
			}
			else{
				state = wait;
			}
			break;

		case led1:
			if(button == 1){
				state = led1;
			}
			else{
				state = init;
			}
			break;
	}

	switch(state){

		case init:

		tmpB = 0x01;

		break;

		case led2:

		tmpB = 0x02;

		break;

		case wait:

		tmpB = 0x02;

		break;

		case led1:

		tmpB = 0x01;

		break;

	}

}



int main(void)

{

	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00;


	state = init;

	while (1)

	{
		button = PINA & 0x01;
		led_Tick();
		PORTB = tmpB;
	}
	return 0;
}
