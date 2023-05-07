
#include "init.h"

void init(void)
{  
	clk_init();
	delay_init();
	output_init();
	input_init();
	uart1_init();
	delay_ms(100);
}
