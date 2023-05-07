/*
 * clock_D21.c
 *
 * Created: 27-Dec-21 7:49:04 PM
 *  Author: PRAVIN
 */ 

#include "clock_D21.h"

void clk_init(void)
{
	osc_48MHz_init();		//CPU CLK(GCLK-0)---> 48MHz.
	gclk_2_init();			//GCLK-2 ---> 4MHz.
	gclk_3_init();		    //GCLK-3 ---> 1.021MHz. /1024 ~1Kz for TC0 running timer

}

void osc_48MHz_init(void)
{
	
	/* ----------------------------------------------------------------------------------------------
	* 1) Set Flash wait states for 48 MHz (per Table 37-40 in data sheet)
	*/
	
	NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_RWS(1);        //wait states to 1
	
	/* ----------------------------------------------------------------------------------------------
	* 2) Enable OSC32K clock (internal 32.768kHz oscillator), will be used as DFLL48M reference.
	*/
	
	uint32_t temp_osc32k_calibration;	/* used to retrieve OSC32K calibration value from NVM */
	// Get factory calibrated value for "OSC32K CAL" from NVM Software Calibration Area
	temp_osc32k_calibration = *(uint32_t*)FUSES_OSC32K_CAL_ADDR;
	temp_osc32k_calibration &= FUSES_OSC32K_CAL_Msk;
	temp_osc32k_calibration = temp_osc32k_calibration>>FUSES_OSC32K_CAL_Pos;
	
	// Configure SYSCTRL->OSC32K settings
	SYSCTRL_OSC32K_Type sysctrl_osc32k = {
		.bit.CALIB = temp_osc32k_calibration,       /* Factory calibration values can be loaded from the non-volatile memory */
		.bit.WRTLOCK = 0,		/* XOSC32K configuration is not locked */
		.bit.STARTUP = 0x2,		/* 3 cycle start-up time */
		.bit.ONDEMAND = 0,		/* Osc. is always running when enabled */
		.bit.RUNSTDBY = 0,		/* Osc. is disabled in standby sleep mode */
		.bit.EN32K = 1,			/* 32kHz output is Enabled */
	};
	// Write these settings
	SYSCTRL->OSC32K.reg=sysctrl_osc32k.reg;
	// Enable the Oscillator
	SYSCTRL->OSC32K.bit.ENABLE = 1;
	
	// Wait for OSC32K to stabilize
	while(!SYSCTRL->PCLKSR.bit.OSC32KRDY);
	
	/* ----------------------------------------------------------------------------------------------
	* 3) Put OSC32K as source of Generic Clock Generator 7
	*/
	
	// Set the Generic Clock Generator 7 output divider to 1
	// Configure GCLK->GENDIV settings
	GCLK_GENDIV_Type gclk7_gendiv = {
		.bit.DIV = 1,			/* Set output division factor = 1 */
		.bit.ID = GCLK_OSC32K  	/* Apply division factor to Generator 7 */
	};
	
	// Write these settings
	GCLK->GENDIV.reg = gclk7_gendiv.reg;
	
	// Configure Generic Clock Generator 7 with XOSC32K as source
	GCLK_GENCTRL_Type gclk7_genctrl = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[7] */
		.bit.OOV = 0,			/* GCLK_IO[7] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x04,		/* Generator source: OSC32K output */
		.bit.ID = GCLK_OSC32K	/* Generator ID: 7 */
	};
	
	// Write these settings
	GCLK->GENCTRL.reg = gclk7_genctrl.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	/* ----------------------------------------------------------------------------------------------
	* 4) Put Generic Clock Generator 7 as source for Generic Clock Multiplexer 0 (DFLL48M reference)
	*/
	
	GCLK_CLKCTRL_Type gclk_clkctrl = {
		.bit.WRTLOCK = 0,		/* Generic Clock is not locked from subsequent writes */
		.bit.CLKEN = 1,			/* Enable the Generic Clock */
		.bit.GEN = GCLK_OSC32K, /* Generic Clock Generator 7 is the source */
		.bit.ID = 0x00			/* Generic Clock Multiplexer 0 (DFLL48M Reference) */
	};
	// Write these settings
	GCLK->CLKCTRL.reg = gclk_clkctrl.reg;
	
	/* ----------------------------------------------------------------------------------------------
	* 5) Enable DFLL48M clock
	*/
	
	// DFLL Configuration in Closed Loop mode, cf product data sheet chapter
	// 17.6.7.1 - Closed-Loop Operation
	
	// Enable the DFLL48M in open loop mode. Without this step, attempts to go into closed loop mode at 48 MHz will
	// result in Processor Reset (you'll be at the in the Reset_Handler in startup_samd21.c).
	// PCLKSR.DFLLRDY must be one before writing to the DFLL Control register
	// Note that the DFLLRDY bit represents status of register synchronization - NOT clock stability
	// (see Data Sheet 17.6.14 Synchronization for detail)
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	SYSCTRL->DFLLCTRL.reg = (uint16_t)(SYSCTRL_DFLLCTRL_ENABLE);
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	// Set up the Multiplier, Coarse and Fine steps
	SYSCTRL_DFLLMUL_Type sysctrl_dfllmul = {
		.bit.CSTEP = 31,		/* Coarse step - use half of the max value (63) */
		.bit.FSTEP = 511,		/* Fine step - use half of the max value (1023) */
		.bit.MUL = 1465			/* Multiplier = MAIN_CLK_FREQ (48MHz) / INT_32K_CLK_FREQ (32768 Hz) */
	};
	// Write these settings
	SYSCTRL->DFLLMUL.reg = sysctrl_dfllmul.reg;
	// Wait for synchronization
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	uint32_t tempDFLL48CalibrationCoarse;	/* used to retrieve DFLL48 coarse calibration value from NVM */
	
	// To reduce lock time, load factory calibrated values into DFLLVAL (cf. Data Sheet 17.6.7.1)
	// Location of value is defined in Data Sheet Table 10-5. NVM Software Calibration Area Mapping
	
	// Get factory calibrated value for "DFLL48M COARSE CAL" from NVM Software Calibration Area
	tempDFLL48CalibrationCoarse = *(uint32_t*)FUSES_DFLL48M_COARSE_CAL_ADDR;
	tempDFLL48CalibrationCoarse &= FUSES_DFLL48M_COARSE_CAL_Msk;
	tempDFLL48CalibrationCoarse = tempDFLL48CalibrationCoarse>>FUSES_DFLL48M_COARSE_CAL_Pos;
	// Write the coarse calibration value
	SYSCTRL->DFLLVAL.bit.COARSE = tempDFLL48CalibrationCoarse;
	// Switch DFLL48M to Closed Loop mode and enable WAITLOCK
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	SYSCTRL->DFLLCTRL.reg |= (uint16_t) (SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_WAITLOCK);
	
	/* ----------------------------------------------------------------------------------------------
	* 6) Switch Generic Clock Generator 0 to DFLL48M. CPU will run at 48MHz.
	*/
	
	// Now that DFLL48M is running, switch CLKGEN0 source to it to run the core at 48 MHz.
	// Enable output of Generic Clock Generator 0 (GCLK_MAIN) to the GCLK_IO[0] GPIO Pin
	GCLK_GENCTRL_Type gclk_genctrl0 = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[0] */
		.bit.OOV = 0,			/* GCLK_IO[0] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x07,		/* Generator source: DFLL48M output */
		.bit.ID = GCLK_MAIN		/* Generator ID: 0 */
	};
	
	GCLK->GENCTRL.reg = gclk_genctrl0.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	/* ----------------------------------------------------------------------------------------------
	* 7) Modify prescaler value of OSC8M to produce 8MHz output
	*/
	
	SYSCTRL->OSC8M.bit.PRESC = 0;		/* Prescale by 1 */
	SYSCTRL->OSC8M.bit.ONDEMAND = 0 ;	/* Oscillator is always on if enabled */
	
	/* ----------------------------------------------------------------------------------------------
	* 8) Set CPU and APBx BUS Clocks to 48MHz
	*/
	PM->CPUSEL.reg  = PM_CPUSEL_CPUDIV_DIV1 ;
	PM->APBASEL.reg = PM_APBASEL_APBADIV_DIV1_Val ;
	PM->APBBSEL.reg = PM_APBBSEL_APBBDIV_DIV1_Val ;
	PM->APBCSEL.reg = PM_APBCSEL_APBCDIV_DIV1_Val ;
}

void gclk_2_init(void)
{
	REG_GCLK_GENDIV = (0x02)|(12<<8);/* Generator ID: 3 */ /* 48MHz/12=4MHZ */
	GCLK_GENCTRL_Type gclk_genctrl2 = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[2] */
		.bit.OOV = 0,			/* GCLK_IO[2] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x07,		/* Generator source: DFLL48M output */
		.bit.ID = 2				/* Generator ID: 2 */
	};
	
	GCLK->GENCTRL.reg = gclk_genctrl2.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
}

void gclk_3_init(void)
{
	REG_GCLK_GENDIV = (0x03)|(47<<8);/* Generator ID: 3 */ /* 48MHz/47=1.021MHZ */
	GCLK_GENCTRL_Type gclk_genctrl3 = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[7] */
		.bit.OOV = 0,			/* GCLK_IO[7] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x07,		/* Generator source: DFLL48M output */
		.bit.ID = 3				/* Generator ID: 3 */
	};
	
	GCLK->GENCTRL.reg = gclk_genctrl3.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
}