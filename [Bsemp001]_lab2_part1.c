/*	Author: brittineysempasa
 *      Partner(s) Name: none
 *	Lab Section:026
 *	Assignment: Lab #2  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	 unsigned char sensor1 = 0x00;
   unsigned char sensor2 = 0x00;

    while (1) {
	      sensor1 = PINA & 0x01;
      	sensor2 = PINA & 0x02;
	      if((sensor1 == 0x01) && (sensor2 == 0x00))
      	{
        	PORTB = 0x01;
      	}
      	else
      	{
        	PORTB = 0x00;
      	}
    }
    return 1;
}
