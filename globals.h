/*
 * globals.h
 * Created: 13-Sep-19 5:02:59 PM
 * Author : PRAVIN
 * VERIFIED: I.KARTHIKEYAN
 */  

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "sam.h"


#define REG_PORTA_PINCFG00		    PORT->Group[0].PINCFG[0].reg
#define REG_PORTA_PINCFG01		    PORT->Group[0].PINCFG[1].reg
#define REG_PORTA_PINCFG02		    PORT->Group[0].PINCFG[2].reg
#define REG_PORTA_PINCFG03		    PORT->Group[0].PINCFG[3].reg
#define REG_PORTA_PINCFG04		    PORT->Group[0].PINCFG[4].reg
#define REG_PORTA_PINCFG05		    PORT->Group[0].PINCFG[5].reg
#define REG_PORTA_PINCFG06		    PORT->Group[0].PINCFG[6].reg
#define REG_PORTA_PINCFG07		    PORT->Group[0].PINCFG[7].reg
#define REG_PORTA_PINCFG08		    PORT->Group[0].PINCFG[8].reg
#define REG_PORTA_PINCFG09		    PORT->Group[0].PINCFG[9].reg
#define REG_PORTA_PINCFG10			PORT->Group[0].PINCFG[10].reg
#define REG_PORTA_PINCFG11			PORT->Group[0].PINCFG[11].reg
#define REG_PORTA_PINCFG12			PORT->Group[0].PINCFG[12].reg
#define REG_PORTA_PINCFG13			PORT->Group[0].PINCFG[13].reg
#define REG_PORTA_PINCFG14		    PORT->Group[0].PINCFG[14].reg
#define REG_PORTA_PINCFG15		    PORT->Group[0].PINCFG[15].reg
#define REG_PORTA_PINCFG16          PORT->Group[0].PINCFG[16].reg
#define REG_PORTA_PINCFG17          PORT->Group[0].PINCFG[17].reg
#define REG_PORTA_PINCFG18          PORT->Group[0].PINCFG[18].reg
#define REG_PORTA_PINCFG19          PORT->Group[0].PINCFG[19].reg
#define REG_PORTA_PINCFG20          PORT->Group[0].PINCFG[20].reg
#define REG_PORTA_PINCFG21          PORT->Group[0].PINCFG[21].reg
#define REG_PORTA_PINCFG22          PORT->Group[0].PINCFG[22].reg
#define REG_PORTA_PINCFG23          PORT->Group[0].PINCFG[23].reg
#define REG_PORTA_PINCFG24          PORT->Group[0].PINCFG[24].reg
#define REG_PORTA_PINCFG25          PORT->Group[0].PINCFG[25].reg
#define REG_PORTA_PINCFG26          PORT->Group[0].PINCFG[26].reg
#define REG_PORTA_PINCFG27		    PORT->Group[0].PINCFG[27].reg
#define REG_PORTA_PINCFG28		    PORT->Group[0].PINCFG[28].reg
#define REG_PORTA_PINCFG29		    PORT->Group[0].PINCFG[29].reg
#define REG_PORTA_PINCFG30		    PORT->Group[0].PINCFG[30].reg
#define REG_PORTA_PINCFG31		    PORT->Group[0].PINCFG[31].reg

#define REG_PORTB_PINCFG00		    PORT->Group[1].PINCFG[0].reg
#define REG_PORTB_PINCFG01		    PORT->Group[1].PINCFG[1].reg
#define REG_PORTB_PINCFG02		    PORT->Group[1].PINCFG[2].reg
#define REG_PORTB_PINCFG03		    PORT->Group[1].PINCFG[3].reg
#define REG_PORTB_PINCFG04		    PORT->Group[1].PINCFG[4].reg
#define REG_PORTB_PINCFG05		    PORT->Group[1].PINCFG[5].reg
#define REG_PORTB_PINCFG06		    PORT->Group[1].PINCFG[6].reg
#define REG_PORTB_PINCFG07		    PORT->Group[1].PINCFG[7].reg
#define REG_PORTB_PINCFG08		    PORT->Group[1].PINCFG[8].reg
#define REG_PORTB_PINCFG09		    PORT->Group[1].PINCFG[9].reg
#define REG_PORTB_PINCFG10			PORT->Group[1].PINCFG[10].reg
#define REG_PORTB_PINCFG11			PORT->Group[1].PINCFG[11].reg
#define REG_PORTB_PINCFG12			PORT->Group[1].PINCFG[12].reg
#define REG_PORTB_PINCFG13			PORT->Group[1].PINCFG[13].reg
#define REG_PORTB_PINCFG14		    PORT->Group[1].PINCFG[14].reg
#define REG_PORTB_PINCFG15		    PORT->Group[1].PINCFG[15].reg
#define REG_PORTB_PINCFG16          PORT->Group[1].PINCFG[16].reg
#define REG_PORTB_PINCFG17          PORT->Group[1].PINCFG[17].reg
#define REG_PORTB_PINCFG18          PORT->Group[1].PINCFG[18].reg
#define REG_PORTB_PINCFG19          PORT->Group[1].PINCFG[19].reg
#define REG_PORTB_PINCFG20          PORT->Group[1].PINCFG[20].reg
#define REG_PORTB_PINCFG21          PORT->Group[1].PINCFG[21].reg
#define REG_PORTB_PINCFG22          PORT->Group[1].PINCFG[22].reg
#define REG_PORTB_PINCFG23          PORT->Group[1].PINCFG[23].reg
#define REG_PORTB_PINCFG24          PORT->Group[1].PINCFG[24].reg
#define REG_PORTB_PINCFG25          PORT->Group[1].PINCFG[25].reg
#define REG_PORTB_PINCFG26          PORT->Group[1].PINCFG[26].reg
#define REG_PORTB_PINCFG27		    PORT->Group[1].PINCFG[27].reg
#define REG_PORTB_PINCFG28		    PORT->Group[1].PINCFG[28].reg
#define REG_PORTB_PINCFG29		    PORT->Group[1].PINCFG[29].reg
#define REG_PORTB_PINCFG30		    PORT->Group[1].PINCFG[30].reg
#define REG_PORTB_PINCFG31		    PORT->Group[1].PINCFG[31].reg

#define REG_PORTA_PMUX00            PORT->Group[0].PMUX[0].reg
#define REG_PORTA_PMUX01            PORT->Group[0].PMUX[1].reg
#define REG_PORTA_PMUX02            PORT->Group[0].PMUX[2].reg
#define REG_PORTA_PMUX03            PORT->Group[0].PMUX[3].reg
#define REG_PORTA_PMUX04            PORT->Group[0].PMUX[4].reg
#define REG_PORTA_PMUX05            PORT->Group[0].PMUX[5].reg
#define REG_PORTA_PMUX06            PORT->Group[0].PMUX[6].reg
#define REG_PORTA_PMUX07            PORT->Group[0].PMUX[7].reg
#define REG_PORTA_PMUX08            PORT->Group[0].PMUX[8].reg
#define REG_PORTA_PMUX09            PORT->Group[0].PMUX[9].reg
#define REG_PORTA_PMUX10            PORT->Group[0].PMUX[10].reg
#define REG_PORTA_PMUX11            PORT->Group[0].PMUX[11].reg
#define REG_PORTA_PMUX12            PORT->Group[0].PMUX[12].reg
#define REG_PORTA_PMUX13            PORT->Group[0].PMUX[13].reg
#define REG_PORTA_PMUX14            PORT->Group[0].PMUX[14].reg
#define REG_PORTA_PMUX15            PORT->Group[0].PMUX[15].reg

#endif /* GLOBALS_H_ */