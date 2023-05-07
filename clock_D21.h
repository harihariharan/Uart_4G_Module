/*
 * clock_D21.h
 *
 * Created: 27-Dec-21 7:49:22 PM
 *  Author: PRAVIN
 */ 


#ifndef CLOCK_D21_H_
#define CLOCK_D21_H_

#include "sam.h"

#define GCLK_MAIN 0
#define GCLK_OSC32K 7

void clk_init(void);
void osc_48MHz_init(void);
void gclk_1_init(void);
void gclk_2_init(void);
void gclk_3_init(void);


#endif /* CLOCK_D21_H_ */