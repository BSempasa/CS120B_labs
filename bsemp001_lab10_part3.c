/*Brittiney Sempasa Bsemp001@ucr.edu
 *Lab Section: 026
 * Assignment: Lab 10 exercise 3
 *
 *I acknowledge all content contained herein, excluding template or example code, 
 *is my own original work
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
//Used timer.h which holds the timer code to keep everything nice to focus on fixing main code

unsigned char tmpA = 0x00;

enum ThreeLEDStates { ThreeLEDs_Start, ThreeLEDs_S0, ThreeLEDs_S1, ThreeLEDs_S2 } ThreeLEDState;
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char blinkCount = 0x01;

void Tick_ThreeLEDs()
{
	switch(ThreeLEDState)
	{
		case ThreeLEDs_Start: 
			ThreeLEDState = ThreeLEDs_S0; 
			break;
		case ThreeLEDs_S0:
			ThreeLEDState = ThreeLEDs_S1; 
			break;
		case ThreeLEDs_S1:
			ThreeLEDState = ThreeLEDs_S2;
			break;
		case ThreeLEDs_S2:
			ThreeLEDState = ThreeLEDs_S0; 
			break;
		default:
			ThreeLEDState = ThreeLEDs_Start; 
			break;
	}

	switch(ThreeLEDState)
	{
		case ThreeLEDs_Start:
			break;
		case ThreeLEDs_S0:
			threeLEDs = 0x01;
			break;
		case ThreeLEDs_S1:
			threeLEDs = 0x02;
			break;
		case ThreeLEDs_S2:
			threeLEDs = 0x04;
			break;
		default: break;
	}
}
enum BlinkLEDStates {BlinkLED_Start, BlinkLED_Blink} BlinkLEDState;
void Tick_BlinkLed()
{
	switch(BlinkLEDState)
	{
		case BlinkLED_Start:
			BlinkLEDState = BlinkLED_Blink;
			break;
		case BlinkLED_Blink:
			BlinkLEDState = BlinkLED_Blink;
			break;
		default:
			BlinkLEDState = BlinkLED_Start;
			break;
	}
	switch(BlinkLEDState)
	{
		case BlinkLED_Start:
			break;
		case BlinkLED_Blink:
			if(blinkCount == 0x01)
			{
				blinkingLED = 0x08;
				blinkCount = 0x00;
			}
			else
			{
				blinkingLED = 0x00;
				blinkCount = 0x01;
			}
			break;
		default:
			break;
	}
}

enum SPEAKERStates { Start, SPEAKER_Wait, SPEAKER_On, SPEAKER_Off } SPEAKERState;
unsigned char sqwak;
void Tick_SPEAKER()
{
	tmpA = ~PINA;
	switch (SPEAKERState)
	{
		case Start:
			SPEAKERState = SPEAKER_Wait;
			break;
		case SPEAKER_Wait:
			if ((tmpA & 0x04) == 0x04)
			{
				SPEAKERState = SPEAKER_On;
			}
			else
			{
				SPEAKERState = SPEAKER_Wait;
			}
			break;

		case SPEAKER_On:
			if (((tmpA & 0x04) == 0x04))
			{
				SPEAKERState = SPEAKER_Off;
			}
			else
			{
				SPEAKERState = SPEAKER_Wait;
			}
			break;

		case SPEAKER_Off:
			if ((tmpA & 0x04) == 0x04)
			{
				SPEAKERState = SPEAKER_On;
			}
			else
			{
				SPEAKERState = SPEAKER_Wait;
			}
			break;

		default:
			SPEAKERState = SPEAKER_Wait;
			break;
	}

	switch (SPEAKERState)
	{
		case Start:
			break;
		case SPEAKER_Wait:
			sqwak = 0;
			break;
		case SPEAKER_On:
			sqwak = 0x10;
			break;
		case SPEAKER_Off:
			sqwak = 0x00;
			break;
		default:
			break;
	}
}

enum CombineStates { CombineLED_Start, CombineLED_Combine } CombineState;
void Tick_CombineLEDs()
{
	switch (CombineState)
	{
		case CombineLED_Start:
			CombineState = CombineLED_Combine;
			break;
		case CombineLED_Combine:
			CombineState = CombineLED_Combine;
			break;
		default:
			CombineState = CombineLED_Combine;
			break;
	}

	switch (CombineState)
	{
		case CombineLED_Start:
			break;
		case CombineLED_Combine:
			PORTB = threeLEDs + blinkingLED + sqwak;
			break;
		default:
			break;
	}
}

int main(void)
{
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	unsigned long SPEAKER_elapsedTime = 0;
	unsigned long CM_elapsedTime = 0;
	const unsigned long timerPeriod = 1;

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(timerPeriod);
	TimerOn();
	
	ThreeLEDState = ThreeLEDs_Start;
	BlinkLEDState = BlinkLED_Start;
	SPEAKERState = Start;
	CombineState = CombineLED_Start;

	while (1)
	{
		if (TL_elapsedTime >= 300)
		{
			Tick_ThreeLEDs();
			TL_elapsedTime = 0;
		}

		if (BL_elapsedTime >= 1000)
		{
			Tick_BlinkLed();
			BL_elapsedTime = 0;
		}

		if (SPEAKER_elapsedTime >= 2)
		{
			Tick_SPEAKER();
			SPEAKER_elapsedTime = 0;
		}

		if (CM_elapsedTime >= 1)
		{
			Tick_CombineLEDs();
			CM_elapsedTime = 0;
		}

		while(!TimerFlag);
		TimerFlag = 0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		SPEAKER_elapsedTime += timerPeriod;
		CM_elapsedTime += timerPeriod;
	}
}