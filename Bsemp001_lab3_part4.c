/*	Author: Brittiney Sempasa
 *  Partner(s) Name: N/A
 *	Lab Section: 026
 *	Assignment: Lab #3  Exercise #4
 *	Exercise Description:
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
    unsigned char tmpAB = 0x00;
  	unsigned char tmpC = 0x00;


    /* Insert your solution below */
    while (1) {
      tmpA = PINA & 0x0F;
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

  		else if(tmpA == 7 || tmpA == 8 || tmpA == 9){
  			tmpC = 0x3C;
  		}

  		else if( tmpA == 10 || tmpA == 11 || tmpA == 12){
  			tmpC = 0x3E;
  		}

  		else if(tmpA == 13 || tmpA == 14 || tmpA == 15){
  			tmpC = 0x3F;
  		}
  		else{
  			tmpC = 0;
  		}

  		if(tmpA < 5){
  			tmpC = tmpC | 0x40;
  		}
  		tmpAB = tmpAB >> 4;

  		if(tmpAB == 3){
  			tmpC = tmpC | 0x80;
  		}

  		PORTC = tmpC;
  	}

    return 1;
}
