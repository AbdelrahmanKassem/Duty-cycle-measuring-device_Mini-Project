  /******************************************************************************
 *
 * Module: miniprojectfinal - application
 *
 * File Name: miniprojectfinal.c
 *
 * Description: the application used to measure duty cycle of an input pulse signal
 * 				using timer 1 and external interrupts and displays the result on lcd
 *
 * Author: Kassem
 *
 *******************************************************************************/

#include "miniprojectfinal.h"

volatile uint8 counter=0;uint32 time[4]={0,0,0,0};uint32 overflow=0;

ISR(INT0_vect) /*interrupt of int0*/
{

	if(counter<4)
	{
		/*when counter is less than 4 we calculate the total number of ticks made by the timer
		 * including overflow to the equation due to the possibility of it
		 * saving the time of each of the first 3 edges of the signal staring with a rising edge
		 */

		time[counter]=(TCNT1 + (overflow * 65535))-time[0];
		counter++; /*increase counter to represent number of edges calculated -1*/
		TOGGLE_BIT(MCUCR,ISC00); /*changing the external interrupt to work on the opposite edge*/
	}

}

void INT0_Init(void)
{
	/*
	 * configurating interrupt 0
	 * enabling int 0
	 * choosing to have an interrupt with every rising edge
	 */
	SET_BIT(GICR,INT0);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(MCUCR,ISC00);

}

void Timer_Callback(void) /*timer call back function*/
{
	overflow++; /*increase overflow count*/
}

void Remeasure(void)
{
	/*
	 * reset all variables to 0
	 * reset timer initial value to 0
	 * reset int0 to work on rising edge
	 */
	counter=0;
	TCNT1=0;
	overflow=0;
	time[0]=0;
	time[1]=0;
	time[2]=0;
	time[3]=0;
	SET_BIT(MCUCR,ISC00);
}



int main(void)
{

	CLEAR_BIT(DDRD,PD2); /*assign pd2 as input for the signal we want to measure*/
	LCD_init(); /*initializing lcd*/
	uint8 string []="Duty Cycle =   %"; /*string that will be printed on the lcd*/
	LCD_displayString(string);/*printing on lcd */
	INT0_Init();/*initializing interrupt*/
	Timer1_init();/*initializing timer 1*/
	Timer1_setCallBack(Timer_Callback); /*sending the address of the callback function to timer 1 driver*/
	int DutyCycle=0;
	while(1)
	{
		if(counter>3)
		{

			DutyCycle=((float)(time[3]-time[2])/(time[3]-time[1]))*(100); /*equation to calculate duty cycle without errors*/
			LCD_goToRowColumn(0 , 14);/*setting cursor location*/
			LCD_integerToString(DutyCycle);/*printing duty cycle value*/
			Remeasure();/*reset everything to start measuring all over again*/
		}
	}

}
