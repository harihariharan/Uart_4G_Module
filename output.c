/*
 * output.c
 *
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 */ 
 #include "output.h"

 void output_init(void)
 {
	 /*************OUTPUT DIRECTION SET***************/
	 REG_PORT_DIR0 |= STATUS_LED1; STATUS_LED1_OFF;
	 REG_PORT_DIR0 |= STATUS_LED2; STATUS_LED2_OFF;
	 REG_PORT_DIR0 |= STATUS_LED3; STATUS_LED3_OFF;
	 REG_PORT_DIR1 |= STATUS_LED4; STATUS_LED4_OFF;
	 
 }