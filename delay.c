/*
 * delay.c
 *
 * Created: 30-Mar-20 10:11:21 AM
 *  Author: PRAVIN
 */ 

#include "delay.h"

void delay_init()
{
	_system_time_init();
}

void _system_time_init()
{
	SysTick->LOAD = (0xFFFFFF << SysTick_LOAD_RELOAD_Pos);
	SysTick->CTRL = (1 << SysTick_CTRL_ENABLE_Pos)| (1 << SysTick_CTRL_CLKSOURCE_Pos);
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of us
 */
static inline uint32_t _get_cycles_for_us_internal(const uint16_t us, const uint32_t freq, const uint8_t power)
{
	switch (power) {
	case 8:
		return (us * (freq / 100000) - 1) / 10 + 1;
	case 7:
		return (us * (freq / 10000) - 1) / 100 + 1;
	case 6:
		return (us * (freq / 1000) - 1) / 1000 + 1;
	case 5:
		return (us * (freq / 100) - 1) / 10000 + 1;
	case 4:
		return (us * (freq / 10) - 1) / 100000 + 1;
	default:
		return (us * freq - 1) / 1000000 + 1;
	}
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of us
 */
uint32_t _get_cycles_for_us(const uint16_t us)
{
	return _get_cycles_for_us_internal(us, CONF_CPU_FREQUENCY, CPU_FREQ_POWER);
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of ms
 */
static inline uint32_t _get_cycles_for_ms_internal(const uint16_t ms, const uint32_t freq, const uint8_t power)
{
	switch (power) {
	case 8:
		return (ms * (freq / 100000)) * 100;
	case 7:
		return (ms * (freq / 10000)) * 10;
	case 6:
		return (ms * (freq / 1000));
	case 5:
		return (ms * (freq / 100) - 1) / 10 + 1;
	case 4:
		return (ms * (freq / 10) - 1) / 100 + 1;
	default:
		return (ms * freq - 1) / 1000 + 1;
	}
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of ms
 */
uint32_t _get_cycles_for_ms(const uint16_t ms)
{
	return _get_cycles_for_ms_internal(ms, CONF_CPU_FREQUENCY, CPU_FREQ_POWER);
}

/**
 * \brief Perform delay in us
 */
void delay_us(const uint16_t us)
{
	_delay_cycles(_get_cycles_for_us(us));
}

/**
 * \brief Perform delay in ms
 */
void delay_ms(const uint16_t ms)
{
	_delay_cycles(_get_cycles_for_ms(ms));
}

void _delay_cycles(uint32_t cycles)
{
	uint8_t  n   = cycles >> 24;
	uint32_t buf = cycles;

	while (n--) {
		SysTick->LOAD = 0xFFFFFF; //ReloadLoad value
		SysTick->VAL  = 0xFFFFFF; //counter value
		while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));  // wait for timer counts to 0
		buf -= 0xFFFFFF;
	}

	SysTick->LOAD = buf;
	SysTick->VAL  = buf;
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // wait for timer counts to 0
}
