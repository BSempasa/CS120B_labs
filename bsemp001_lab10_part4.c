/*
 * lab10_part4.c
 *
 * Created: 5/17/2020 7:23:09 PM
 * Author : 19514
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

unsigned char tmpA = 0x00;

enum ThreeLEDStates { ThreeLEDs_Start, ThreeLEDs_S0, ThreeLEDs_S1, ThreeLEDs_S2 } ThreeLEDState;
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char blinkCount = 0x01;

void Tick_ThreeLEDs()
{
	switch(ThreeLEDState)
	{
		case ThreeLEDs_Start: ThreeLEDState = ThreeLEDs_S0; break;
		case ThreeLEDs_S0:
		ThreeLEDState = ThreeLEDs_S1; break;
		case ThreeLEDs_S1:
		ThreeLEDState = ThreeLEDs_S2; break;
		case ThreeLEDs_S2:
		ThreeLEDState = ThreeLEDs_S0; break;
		default:
		ThreeLEDState = ThreeLEDs_Start; break;
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
		default: 
			break;
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

enum SpeakerStates { Speaker_Start, Speaker_Wait, Speaker_On, Speaker_Off } SpeakerState;
unsigned char pulse = 1;
unsigned char Speaker_counter = 1;
unsigned char speak;
void Tick_speaker()
{
	tmpA = ~PINA;
	switch (SpeakerState)
	{
		case Speaker_Start:
		SpeakerState = Speaker_Wait;
		break;

		case Speaker_Wait:
			if ((tmpA & 0x04) == 0x04)
			{
				SpeakerState = Speaker_On;
			}
			else
			{
				SpeakerState = Speaker_Wait;
			}
			break;
		case Speaker_On:
			if (((tmpA & 0x04) == 0x04))
			{
				if (Speaker_counter < pulse)
				{
					SpeakerState = Speaker_On;
				}
				else
				{
					SpeakerState = Speaker_Off;
				}
			}
			else
			{
				SpeakerState = Speaker_Wait;
			}
			break;
		case Speaker_Off:
			if ((tmpA & 0x04) == 0x04)
			{
				if (Speaker_counter < pulse)
				{
					SpeakerState = Speaker_Off;
				}
				else
				{
					SpeakerState = Speaker_On;
				}
			}
			else
			{
				SpeakerState = Speaker_Wait;
			}
			break;
		default:
			SpeakerState = Speaker_Wait;
			break;
	}

	switch (SpeakerState)
	{
		case Speaker_Start:
			break;

		case Speaker_Wait:
			Speaker_counter = 1;
			speak = 0;
			break;

		case Speaker_On:
			if (Speaker_counter < pulse)
			{
				++Speaker_counter;
			}
			else
			{
				Speaker_counter = 1;
			}
			speak = 0x10;
			break;

		case Speaker_Off:
			if (Speaker_counter < pulse)
			{
				++Speaker_counter;
			}
			else
			{
				Speaker_counter = 1;
			}
			speak = 0x00;
			break;
		default:
			break;
	}
}

enum State {Start,Wait,High,Low } State;
void Tick_state()
{
	tmpA = ~PINA;
	switch (State)
	{
		case Start:
			State = Wait;
			break;
		case Wait:
			if (tmpA & 0x03)
			{
				State = High;
			}
			else
			{
				State = Wait;
			}
			break;
		case High:
			State = Low;
			break;
		case Low:
			if (tmpA & 0x03)
			{
				State = Low;
			}
			else
			{
				State = Wait;
			}
			break;

		default:
			State = High;
			break;
	}

	switch (State)
	{
		case Start:
			break;
		case Wait:
			break;
		case High:
			if ((tmpA & 0x03) == 0x01)
			{
				if (pulse > 1)
				{
					--pulse;
				}
			}
			else if ((tmpA & 0x03) == 0x02)
			{
				if (pulse < 8)
				{
					++pulse;
				}
			}
			break;

		case Low:
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
			PORTB = threeLEDs + blinkingLED + speak;
			break;
		default:
			break;
	}
}

int main(void)
{
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	unsigned long speaker_elapsedTime = 0;
	unsigned long state_elapsedTime = 0;
	unsigned long CM_elapsedTime = 0;
	const unsigned long timerPeriod = 1;

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(timerPeriod);
	TimerOn();
	
	ThreeLEDState = ThreeLEDs_Start;
	BlinkLEDState = BlinkLED_Start;

	SpeakerState = Speaker_Start;
	State = Start;
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

		if (speaker_elapsedTime >= 1)
		{
			Tick_speaker();
			speaker_elapsedTime = 0;
		}

		if (state_elapsedTime >= 50)
		{
			Tick_state();
			state_elapsedTime = 0;
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
		speaker_elapsedTime += timerPeriod;
		state_elapsedTime += timerPeriod;
		CM_elapsedTime += timerPeriod;
	}
}
