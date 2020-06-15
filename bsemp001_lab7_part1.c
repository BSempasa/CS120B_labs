/*    Partner(s) Name & E-mail: Brittiney Sempasa
 *    Lab Section: 026
 *    Assignment: Lab #7  Exercise #1
 * 
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#include _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#include <avr/interrupt.h>
#endif

enum state {init, wait, incre, decre, reset} state;

unsigned char button0 = 0x00;
unsigned char button1 = 0x00;
unsigned char cnt = 0x00;

void numberCruncher(){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;
	//transitions
	switch(state){
		case init:
			state = wait;
			break;
		case wait:
			if(button0 && button1)
				state = reset;
			else if(button0 && !button1)
				state = incre;
			else if(!button0 && button1)
				state = decre;
			else
				state = wait;
			break;
		case incre:
			if(button0 && button1)
				state = reset;
			else if(button0 && !button1)
				state = incre;
			else
				state = wait;
			break;
		case decre:
			if(button0 && button1)
				state = reset;
			else if(!button0 && button1)
				state = decre;
			else
				state = wait;
			break;
		case reset:
			if(button0 && button1)
				state = reset;
			else
				state = wait;
			break;
		default:
			state = init;
			break;
	}
	
	//state actions
	switch(state){
		case init:
			break;
		case wait:
			break;
		case incre:
			if(cnt < 9)
				cnt++;
			break;
		case decre:
			if(cnt > 0)
				cnt--;
			break;
		case reset:
			cnt = 0;
			break;
		default:
			break;
	}
}

//timer start
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A =125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
};


void TimerOff(){
	TCCR1B = 0x00;
};

void TimerISR(){
	TimerFlag = 1;
};

ISR(TIMER1_COMPA_vect){

	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr ==0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
//timer end

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //initialize port A to input
	DDRC = 0xFF; PORTC = 0x00; //initialize port C to output
	DDRD = 0xFF; PORTD = 0x00; //initialize port D to output
	
	TimerSet(1000);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();
	cnt = 0;
	state = init;
	
    while (1) {
		numberCruncher();
		LCD_ClearScreen();
		LCD_WriteData(cnt + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
    }
}


