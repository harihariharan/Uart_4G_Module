/*
 * input.c
 * 
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 */  

#include "input.h"


void input_init(void)
{	
	REG_PORTB_PINCFG02|=0x02;
	REG_PORTB_PINCFG03|=0x02;
	REG_PORT_CTRL1|=((1<<2)|(1<<3));
	
	REG_PORTA_PINCFG10|=0x02;
	REG_PORTA_PINCFG11|=0x02;
	REG_PORT_CTRL0|=((1<<10)|(1<<11));

}