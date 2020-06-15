/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 11 exercise 4
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "io.h"
#include "timer.h"
#include "stdio.h"

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
    unsigned long int c;
    while(1){
        c = a%b;
        if(c==0){return b;}
        a = b;
        b = c;
    }
    return 0;
}

typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long int period; //Task period
    unsigned long int elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int); //Task tick function
} task;

char keypadChar = 0;
char column = 1;
char newInput = 0;

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

enum SM1_States { SM1_Start, SM1_wait, SM1_keypadPress };

int SMTick1(int state)
{
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
            break;
        case SM1_keypadPress:   
            switch (keypadPress) {
				asm("nop");
                case '\0': 
					newInput = 0; 
					break;
                case '0': 
					keypadChar = '0'; 
					newInput = 1;
					break;
                case '1': 
					keypadChar = '1';
					newInput = 1;
					break; 
                case '2': 
					keypadChar = '2'; 
					newInput = 1;
					break;
                case '3': 
					keypadChar = '3';
					newInput = 1;
					break;
                case '4': 
					keypadChar = '4'; 
					newInput = 1;
					break;
                case '5': 
					keypadChar = '5'; 
					newInput = 1;
					break;
                case '6': 
					keypadChar = '6'; 
					newInput = 1;
					break;
                case '7': 
					keypadChar = '7'; 
					newInput = 1;
					break;
                case '8': 
					keypadChar = '8'; 
					newInput = 1;
					break;
                case '9': 
					keypadChar = '9';
					newInput = 1;
					break;
                case 'A': 
					keypadChar = 'A'; 
					newInput = 1;
					break;
                case 'B': 
					keypadChar = 'B'; 
					newInput = 1;
					break;
                case 'C': 
					keypadChar = 'C'; 
					newInput = 1;
					break;
                case 'D': 
					keypadChar = 'D'; 
					newInput = 1;
					break;
                case '*': 
					keypadChar = '*'; 
					newInput = 1;
					break;
                case '#': 
					keypadChar = '#'; 
					newInput = 1;
					break;
                default: 
					keypadChar = 0x20; 
					break; 
            }
            break;
        default:        
			break;
    }
    return state;
}


enum SM2_States { SM2_Start, SM2_Display };

int SMTick2(int state)
{
    switch (state)
    {
        case SM2_Start:
			state = SM2_Display;
			break; 
        case SM2_Display:
			break;       
        default:
			state = SM2_Display;
			break;
    }
    switch (state)
    {
        case SM2_Start:
            break;
        
        case SM2_Display:
			if(newInput != 0){
				if(column < 17){
					asm("nop");
					LCD_Cursor(column);
					if (keypadChar)
					{
						LCD_WriteData(keypadChar);
					}
					column++;
					newInput = 0;
					asm("nop");
					break;
				}
				else {
					column = 1;
					LCD_Cursor(column);
					if (keypadChar)
					{
						LCD_WriteData(keypadChar);
					}
					newInput = 0;
					asm("nop");
					break;
				}
			}
			break;
			default:
				break;
    }
    return state;
}

int main()
{
    DDRA = 0xFF; PORTA = 0x00; 
    DDRC = 0xF0; PORTC = 0x0F; 
    DDRD = 0xFF; PORTD = 0x00; 

    unsigned long int SMTick1_calc = 50;
    unsigned long int SMTick2_calc = 500;

    unsigned long int tmpGCD = 1;
    tmpGCD = findGCD (SMTick1_calc, SMTick2_calc);

    unsigned long int GCD = tmpGCD;

    unsigned long int SMTick1_period = SMTick1_calc / GCD;
    unsigned long int SMTick2_period = SMTick2_calc / GCD;
 
    static task task1, task2;
    task *tasks[] = { &task1, &task2 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

    task1.state = -1; 
    task1.period = SMTick1_period;
    task1.elapsedTime = SMTick1_period;
    task1.TickFct = &SMTick1;

    LCD_init();
    task2.state = -1; 
    task2.period = SMTick2_period; 
    task2.elapsedTime = SMTick2_period; 
    task2.TickFct = &SMTick2;

    TimerSet(GCD);
    TimerOn();
	
	LCD_DisplayString(1,"Congratulations");
	
    unsigned short i;
    while(1)
    {
        for ( i = 0; i < numTasks; i++ )
        {
            if ( tasks[i]->elapsedTime == tasks[i]->period )
            {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 0;
}