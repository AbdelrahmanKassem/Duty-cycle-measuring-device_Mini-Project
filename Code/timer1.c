  /******************************************************************************
 *
 * Module:TIMER1 (Overflow mode) - Driver
 *
 * File Name: timer1.c
 *
 * Description: driver used to operate timer 1 in overflow mode with interrupt.s
 *
 * Author: Kassem
 *
 *******************************************************************************/


#include "timer1.h"

static volatile void (*g_timer1CallBackPtr)(void) ;/*pointer that holds address of callback function*/

ISR (TIMER1_OVF_vect) /*interrupt*/
{
	g_timer1CallBackPtr();  /*call back pointer*/
}

void Timer1_init(void)
{
	/*
	 * configuring timer 1 in overflow mode
	 * setting initial value to zero
	 * enabling interrupt
	 */
	SREG=(1<<7);
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = 1;
	TCNT1 = 0;
	TIMSK = (1<<TOIE1);
}

void Timer1_setCallBack(void(*a_Ptr)(void)) /*function that sets the pointer with the address to the call back function*/
{
		g_timer1CallBackPtr = a_Ptr;
}


