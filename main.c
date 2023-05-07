/*
 * UART_4G_Interface.c
 *
 * Created: 24-03-2023 16:50:58
 * Author : 91994
 */ 


#include "sam.h"
#include "init.h"


int main(void)
{
    int count = 1;
    char a = '"';
	
	SystemInit();
    init();
	
	/* Replace with your application code */
    while (1) 
    {
		/*STATUS_LED4_OFF; STATUS_LED1_ON; delay_ms(1000);
		STATUS_LED1_OFF; STATUS_LED2_ON; delay_ms(1000);
		STATUS_LED2_OFF; STATUS_LED3_ON; delay_ms(1000);
		STATUS_LED3_OFF; STATUS_LED4_ON; delay_ms(1000);*/
		
		if(DIP_01_STAT==0) {count++;}		 
		UART1_put_text("AT"); UART1_put_text("\r\n"); 
		delay_ms(1000);
		 	
		if(DIP_01_STAT==0) {count++;}		
		UART1_put_text("AT+HTTPINIT"); UART1_put_text("\r\n"); 
		delay_ms(1000);
		
		if(DIP_01_STAT==0) {count++;}			
		UART1_put_text("AT+HTTPPARA=\"URL\",\"https://api.thingspeak.com/update?api_key=N1HNH50VCZDY4X3G&field1=");
		UART1_put_int(count); UART1_put_char(a); UART1_put_text("\r\n");
		delay_ms(1000); 
		
		if(DIP_01_STAT==0) {count++;}		
		UART1_put_text("AT+HTTPACTION=0"); UART1_put_text("\r\n");		
		delay_ms(1000); 	
	}
}
