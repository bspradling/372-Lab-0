/* 
* File:   initLab0.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef INITLAB0_H
#define	INITLAB0_H


//Use defines for pin settings to make your code
#define LED1 LATBbits.LATB15
#define LED2 LATBbits.LATB14
#define LED3 LATBbits.LATB13
#define LED4 LATBbits.LATB12

#define OFF 1;
#define ON 0;

void initLEDs();
void initSW1();
void initTimer1();
void initCN();

#endif	/* INITLAB0_H */

