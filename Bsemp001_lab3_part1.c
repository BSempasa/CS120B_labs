/*	Author: Brittiney Sempasa
 *  Partner(s) Name: N/A
 *	Lab Section: 021
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: Count the number of 1s on ports A and B and output
                          that number on port C.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k)
 {
	return ((x & (0x01 << k))!= 0);
 }

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char button = 0x00;
    /* Insert your solution below */
    while (1) {
      tmpA = PINA;
		  tmpB = PINB;

		   button = 0x00;
		   for(int i = 0; i < 8; i++)
       {
			      if(GetBit(tmpA, i))
            {
				          button++;
			      }
		   }
       for(int i = 0; i < 8; i++)
       {
			    if(GetBit(tmpB, i))
          {
				      button++;
			    }
		   }

		PORTC = button;
    }

    return 1;
}
