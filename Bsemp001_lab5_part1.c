/*	Author: Brittiney Sempasa
 *  Partner(s) Name: N/A
 *	Lab Section: 026
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: A car has a fuel-level sensor that sets PA3..PA0 to a
                          value between 0 (empty) and 15 (full). A series of
                          LEDs connected to PC5..PC0 should light to graphically
                          indicate the fuel level. If the fuel level is 1 or 2,
                          PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
                          Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12
                          lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6
                          connects to a "Low fuel" icon, which should light if
                          the level is 4 or less.  (The example below shows the
                          display for a fuel level of 3).
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
	DDRC = 0xFF; PORTC = 0x00;

  unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
    /* Insert your solution below */
    while (1) {

      tmpA = ~PINA & 0x0F;
      tmpC = 0x00;

      if(tmpA == 1 || tmpA == 2)
      {
			  tmpC = 0x20;
		  }

		  else if(tmpA == 3 || tmpA == 4)
      {
			  tmpC = 0x30;
		  }

		else if(tmpA == 5 || tmpA == 6){
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

		if(tmpA <= 4){
			tmpC = tmpC | 0x40;
		}

		PORTC = tmpC;

    }
    return 1;
}
