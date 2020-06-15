/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 8 Exercise 3
 *
 *
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */  

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void) {
	unsigned short max = 200;
	unsigned char output = 0x00;
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	
	while(1) {
		unsigned short x = ADC;
		if (x > max) {
			max = x;
			} else if (x >= max/2) {
			output = 0x01;
			} else {
			output = 0x00;
		}
		PORTB = output;
	}
	return 1;
}