/*	Author: Brittiney Sempasa
 *  Partner(s) Name: N/A
 *	Lab Section: 026
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: In addition to the above, PA4 is 1 if a key is in the
                          ignition, PA5 is one if a driver is seated, and PA6 is
                          1 if the driver's seatbelt is fastened. PC7 should
                          light a "Fasten seatbelt" icon if a key is in the
                          ignition, the driver is seated, but the belt is not
                          fastened.
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
	  DDRC = 0xFF; PORTC = 0x00;

    unsigned char tmpA = 0x00;
  	unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;


    /* Insert your solution below */
    while (1) {
      tmpA = PINA & 0x0F;
      tmpB = PINA & 0x70;
      tmpC = 0x00;

      if(tmpA == 1 || tmpA == 2)
        {
  			     tmpC = 0x20;
  		  }

  		else if(tmpA == 3 || tmpA == 4)
        {
    			tmpC = 0x30;
    		}

  		else if(tmpA == 5 || tmpA == 6)
      {
  			tmpC = 0x38;
  		}

  		else if(tmpA == 7 || tmpA == 8 || tmpA == 9)
      {
  			tmpC = 0x3C;
  		}

  		else if( tmpA == 10 || tmpA == 11 || tmpA == 12)
      {
  			tmpC = 0x3E;
  		}

  		else if(tmpA == 13 || tmpA == 14 || tmpA == 15)
      {
  			tmpC = 0x3F;
  		}

  		else
      {
  			tmpC = 0;
  		}

  		if(tmpA < 5)
      {
  			tmpC = tmpC | 0x40;
  		}

  		tmpB = tmpB >> 4;

  		if(tmpB == 3)
      {
  			tmpC = tmpC | 0x80;
  		}

  		PORTC = tmpC;
  	}

    return 1;
}
