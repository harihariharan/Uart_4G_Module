/*
 * delay.h
 *
 * Created: 30-Mar-20 10:11:47 AM
 *  Author: PRAVIN
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include "sam.h"

#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 48000000
#endif

#if CONF_CPU_FREQUENCY < 1000
#define CPU_FREQ_POWER 3
#elif CONF_CPU_FREQUENCY < 10000
#define CPU_FREQ_POWER 4
#elif CONF_CPU_FREQUENCY < 100000
#define CPU_FREQ_POWER 5
#elif CONF_CPU_FREQUENCY < 1000000
#define CPU_FREQ_POWER 6
#elif CONF_CPU_FREQUENCY < 10000000
#define CPU_FREQ_POWER 7
#elif CONF_CPU_FREQUENCY < 100000000
#define CPU_FREQ_POWER 8
#endif

#define CONF_SYSTICK_TICKINT 0

uint32_t _get_cycles_for_us(const uint16_t us);
uint32_t _get_cycles_for_ms(const uint16_t ms);
void delay_init();
void delay_us(const uint16_t us);
void delay_ms(const uint16_t ms);
void _delay_cycles(uint32_t cycles);
void _system_time_init();


/*refer the link for Systick Register summary
https://microchipdeveloper.com/32arm:samd21-systick
*/


#endif /* DELAY_H_ */