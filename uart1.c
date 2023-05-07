/*
 * uart1.c
 *
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 */ 

#include "uart1.h"
#include "globals.h"

void uart1_init()
{
	/* Clock and PIN config */
	//REG_GCLK_PCHCTRL19 |= (1<<6);  // GCLK0 48Mhz Enable
	//REG_MCLK_APBCMASK |= (1<<1); //M-Clk Enable
	
	REG_GCLK_CLKCTRL=(0x17)|(1<<14); //GCLK ENABLE, Select GCLK 0 , Gclk id- SERCOM3
	REG_PM_APBCMASK |=(1<<5);  //Mclk
	
	REG_PORTA_PINCFG20 |= (1<<0);  // PA20 Mux Enable
	REG_PORTA_PINCFG21 |= (1<<0);  // PA21 Mux Enable
	REG_PORTA_PMUX10 |= 0x33; // Peripheral func - SERCOM3
	
	
	/* UART INIT */
	
	REG_SERCOM3_USART_CTRLA |= (1<<2);  //Internal Clock Enabled
	REG_SERCOM3_USART_CTRLA |= (1<<30); // LSB Transmitted first
	REG_SERCOM3_USART_CTRLA |= (1<<20)|(1<<21); // PAD[3] for Data Reception RXD
	REG_SERCOM3_USART_CTRLA |= (1<<16); // PAD[2] for Data Transmission TXD

	SERCOM3_UART_SYNC_WAIT;
	
	REG_SERCOM3_USART_CTRLB |= (1<<16); // Transmitter Enable
	REG_SERCOM3_USART_CTRLB |= (1<<17); //receiver Enable
	
	SERCOM3_UART_SYNC_WAIT;
	
	if (SERCOM3_UART_INTERRUPT_ENABLE)
	{
		REG_SERCOM3_USART_INTFLAG|=(1<<2);  ////Receive complete interrupt clear
		REG_SERCOM3_USART_INTENSET |= (1<<2); //Receive complete interrupt enable
		
		NVIC_SetPriority(SERCOM3_IRQn,0);		// set  interrupt priority
		NVIC_ClearPendingIRQ(SERCOM3_IRQn);		// clear pending  interrupts
		NVIC_EnableIRQ(SERCOM3_IRQn);	//ISR (Handler) Enable
	}
	SERCOM3_UART_SYNC_WAIT;
	SET_9600_AS_BAUD;
	SERCOM3_UART_SYNC_WAIT;
	REG_SERCOM3_USART_CTRLA |= (1<<1); // SERCOM3 UART Enable
}

void SERCOM3_Handler(void)
{
	if( REG_SERCOM3_USART_INTFLAG &(1<<2))
	{
		char data = REG_SERCOM3_USART_DATA;  //data must be read after receive complete else interrupt will be generated continuously and cpu will never leave th handler
		REG_SERCOM3_USART_INTFLAG|=(1<<2);	//CLEAR FLAG
	}
	if( REG_SERCOM3_USART_INTFLAG &(1<<1))
	{
		REG_SERCOM3_USART_INTFLAG|=(1<<1);	//CLEAR FLAG
	}
}

void UART1_put_char(char c)
{
	
	while((REG_SERCOM3_USART_INTFLAG & 0x01)!= 1); //check data reg empty
	REG_SERCOM3_USART_DATA = c;
	while((REG_SERCOM3_USART_INTFLAG & 0x02)!= 2); //transmit complete
	
}

char UART1_get_char()
{
	char c;
	while((REG_SERCOM3_USART_INTFLAG & 0x04)!= 4); //receive complete flag check
	c=REG_SERCOM3_USART_DATA;
	if(UART1_PRINTBACK)
	UART1_put_char(c) ;
	return(c);
}

void UART1_put_text(char c[])
{
	uint8_t position=0;
	while( c[ position ] != '\0' )
	{
		UART1_put_char( c[ position ] ) ;
		++position ;
	}
}

void UART1_put_int(uint32_t number)
{
	char ascii_number[ 11 ];

	UART1_uitoa( number, ascii_number ) ;
	UART1_put_text( ascii_number ) ;
}

void UART1_get_text(char* data)
{
	do {
		*(data) = UART1_get_char() ;
		data++;
	} while( *(data-1) != 0x0D ) ;
	*(data) = '\0' ;
}

uint32_t UART1_get_int()
{
	uint32_t number=0;
	uint8_t temp=0;
	temp =UART1_get_char();
	while(temp!=0x0D)
	{
		if (( temp >= '0' ) && ( temp <= '9' ))
		{
			number=((number*10)+(temp-'0'));
		}
		temp =UART1_get_char();
	}
	return number;
}

void UART1_uitoa(uint32_t number, char* ascii_number)
{
	uint8_t position=0;
	uint8_t length=0 ;
	uint32_t temp_int=number;

	if (number==0)
	{
		*( ascii_number)='0';
		*( ascii_number+1)='\0';
	}
	else
	{
		while (temp_int)
		{
			temp_int/=10;
			length++;
		}
		for (position=length;position>0;position--)
		{
			*( ascii_number + position-1) = '0' + number % 10;
			number /= 10;
		}
		*( ascii_number + length) = '\0';
	}
}
