/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 11 exercise 1
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include "stdio.h"

typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long int period; //Task period
    unsigned long int elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int); //Task tick function
} task;


unsigned char GetKeypadKey() {

    PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('1'); }
    if (GetBit(PINC,1)==0) { return('4'); }
    if (GetBit(PINC,2)==0) { return('7'); }
    if (GetBit(PINC,3)==0) { return('*'); }

    // Check keys in col 2
    PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('2'); }
    if (GetBit(PINC,1)==0) { return('5'); }
    if (GetBit(PINC,2)==0) { return('8'); }
    if (GetBit(PINC,3)==0) { return('0'); }

    // Check keys in col 3
    PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('3'); }
    if (GetBit(PINC,1)==0) { return('6'); }
    if (GetBit(PINC,2)==0) { return('9'); }
    if (GetBit(PINC,3)==0) { return('#'); }

    // Check keys in col 4
    PORTC = 0x7F; // Enable col 7 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('A'); }
    if (GetBit(PINC,1)==0) { return('B'); }
    if (GetBit(PINC,2)==0) { return('C'); }
    if (GetBit(PINC,3)==0) { return('D'); }

    return('\0'); // default value

}

enum SM1_States { SM1_Start, SM1_wait, SM1_keypadPress};


int SMTick1(int state) {

    unsigned char keypadPress = GetKeypadKey();
    
    switch (state) {
    case SM1_Start:
        state = SM1_wait;
        break;
        
    case SM1_wait:
        if(keypadPress != '\0'){
            state = SM1_keypadPress;
        }   
        break;

    case SM1_keypadPress:   
        if(keypadPress == '\0'){
            state = SM1_wait;
        }else{
            state = SM1_keypadPress;
        }
        break;
        
    default:        
        state = SM1_wait; 
        break;
    }

    switch(state) {
        case SM1_wait:  
            keypadPress = 0x1F;

        case SM1_keypadPress:   
            switch (keypadPress) {
                case '\0':
					PORTB = 0x1F; 
					break; 
                case '0': 
					PORTB = 0x00; 
					break;
                case '1': 
					PORTB = 0x01; 
					break; 
                case '2': 
					PORTB = 0x02; 
					break;
                case '3': 
					PORTB = 0x03; 
					break;
                case '4': 
					PORTB = 0x04; 
					break;
                case '5': 
					PORTB = 0x05; 
					break;
                case '6': 
					PORTB = 0x06; 
					break;
                case '7': 
					PORTB = 0x07; 
					break;
                case '8': 
					PORTB = 0x08; 
					break;
                case '9': 
					PORTB = 0x09; 
					break;
                case 'A': 
					PORTB = 0x0A; 
					break;
                case 'B': 
					PORTB = 0x0B; 
					break;
                case 'C': 
					PORTB = 0x0C; 
					break;
                case 'D': 
					PORTB = 0x0D; 
					break;
                case '*': 
					PORTB = 0x0E; 
					break;
                case '#': 
					PORTB = 0x0F; 
					break;
                default: 
					PORTB = 0x1F; 
					break; 
				}
				break;

			default:        
				break;
    }

    return state;
}

int main()
{
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;

    static task task1;
    task *tasks = &task1;

    task1.state = -1;
    task1.period = 50;
    task1.TickFct = &SMTick1;

    TimerSet(50);
    TimerOn();

    unsigned short i;
    while(1) {
        for ( i = 0; i < 1; i++ ) {
                tasks->state = tasks->TickFct(tasks->state);
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }

}