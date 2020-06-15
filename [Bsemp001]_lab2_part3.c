/*	Author: Brittiney Sempasa
 *      Partner(s) Name: none
 *	Lab Section:026
 *	Assignment: Lab #2  Exercise #3
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
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
	unsigned char parkspot = 0x00;
        unsigned char cntavail = 0x00;

    while (1) {
	parkspot = PINA & 0x0F;
	if((parkspot ==0x01)||(parkspot ==0x02)||(parkspot ==0x04)||(parkspot ==0x08))
      	{
        	cntavail =0x03;
      	}
	else if((parkspot ==0x03)||(parkspot ==0x05)||(parkspot ==0x06)||(parkspot ==0x09)||(parkspot ==0x0A)||(parkspot ==0x0C))
      	{
        	cntavail = 0x02;
      	}
	else if((parkspot ==0x07)||(parkspot ==0x0B)||(parkspot ==0x0D)||(parkspot ==0x0E))
      	{
        	cntavail = 0x01;
      	}
	else if (parkspot == 0x0F)
      	{
        	cntavail = 0x80;
      	}
	else
      	{
        	cntavail = 0x04;
      	}
    }

    return 1;
}
