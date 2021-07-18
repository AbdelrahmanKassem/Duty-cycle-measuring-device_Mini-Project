 /******************************************************************************
 *
 * Module: timer 1 (overflow) - Configuration
 *
 * File Name: timer1.h
 *
 * Description: timer1.h which holds all function prototypes and definitions of the timer1.c
 * 				and also important libraries used by timer1.c
 *
 * Author: Kassem
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

/******************************Libraries********************************/

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**************************Function Prototypes************************/

void Timer1_init(void);
void Timer1_setCallBack(void(*a_Ptr)(void));


#endif /* TIMER1_H_ */
