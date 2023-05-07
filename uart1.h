/*
 * uart1.h
 * 
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 */ 

#ifndef UART1_H_
#define UART1_H_

#include "sam.h"

//SERCOM5 PAD2 is UART_Tx PA20
//SERCOM5 PAD3 is UART_Rx PA21

#define SERCOM3_UART_INTERRUPT_ENABLE	ENABLE
#define ENABLE 1
#define DISABLE	0
#define UART1_PRINTBACK  ENABLE

#define SERCOM3_CLK_EN (1<<3)
#define SERCOM3_UART_SYNC_WAIT {while (REG_SERCOM3_USART_SYNCBUSY!=0);}

#define UART1_DATA_REGISTER REG_SERCOM3_USART_DATA


//STOP BITS
#define  UART1_SET_STOPBIT_1  REG_SERCOM3_USART_CTRLB &=~(1<<6)
#define  UART1_SET_STOPBIT_2  REG_SERCOM3_USART_CTRLB |=(1<<6)

#define  UART1_ENABLE  REG_SERCOM3_USART_CTRLA |= (1<<1); // UART1 SERCOM0 Enable
#define  UART1_DISABLE REG_SERCOM3_USART_CTRLA &= ~(1<<1); // UART1 SERCOM0  disable

#define  SET_9600_AS_BAUD	REG_SERCOM3_USART_BAUD = 65326;
#define  SET_14400_AS_BAUD	REG_SERCOM3_USART_BAUD = 65221;
#define  SET_19200_AS_BAUD	REG_SERCOM3_USART_BAUD = 65116;
#define  SET_38400_AS_BAUD	REG_SERCOM3_USART_BAUD = 64697;
#define  SET_56000_AS_BAUD	REG_SERCOM3_USART_BAUD = 64312;
#define  SET_57600_AS_BAUD	REG_SERCOM3_USART_BAUD = 64277;
#define  SET_115200_AS_BAUD REG_SERCOM3_USART_BAUD = 63019;

void uart1_init(void);
void UART1_put_char(char c);
char UART1_get_char();
void UART1_put_text(char c[]);
void UART1_get_text(char* data);

void UART1_put_int(uint32_t number);
uint32_t UART1_get_int();

void UART1_uitoa(uint32_t number, char* ascii_number);



#endif /* UART1_H_ */
