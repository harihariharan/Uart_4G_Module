/*
 * output.h
 *
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 */ 


#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "sam.h"

#define STATUS_LED1			PORT_PA24
#define STATUS_LED1_ON		REG_PORT_OUTSET0 = STATUS_LED1
#define STATUS_LED1_OFF		REG_PORT_OUTCLR0 = STATUS_LED1
#define STATUS_LED1_TOGGLE  REG_PORT_OUTTGL0 = STATUS_LED1

#define STATUS_LED2			PORT_PA25
#define STATUS_LED2_ON		REG_PORT_OUTSET0 = STATUS_LED2
#define STATUS_LED2_OFF		REG_PORT_OUTCLR0 = STATUS_LED2
#define STATUS_LED2_TOGGLE  REG_PORT_OUTTGL0 = STATUS_LED2

#define STATUS_LED3			PORT_PA23
#define STATUS_LED3_ON		REG_PORT_OUTSET0 = STATUS_LED3
#define STATUS_LED3_OFF		REG_PORT_OUTCLR0 = STATUS_LED3
#define STATUS_LED3_TOGGLE  REG_PORT_OUTTGL0 = STATUS_LED3

#define STATUS_LED4			PORT_PB23
#define STATUS_LED4_ON		REG_PORT_OUTSET1 = STATUS_LED4
#define STATUS_LED4_OFF		REG_PORT_OUTCLR1 = STATUS_LED4
#define STATUS_LED4_TOGGLE  REG_PORT_OUTTGL1 = STATUS_LED4


void output_init(void);


#endif /* OUTPUT_H_ */