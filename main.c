
/*    Partner(s) Name & E-mail: Brittiney Sempasa and Bsemp001@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab #2  Exercise #1
 *    Exercise Description: Garage open at night-- A garage door sensor connects to PA0 (1 means door open), 
	  and a light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates an
	  LED connected to PB0 (1 means illuminate) if the garage door is open at night.
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
    while (1) 
    {
		if(PINA == 0x01) {
			PORTB = 0x01;
		}
		
		else {
			PORTB = 0x00;
		}
    }
}

