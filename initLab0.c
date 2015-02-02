/*
* File:   initLab0.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

#define twoSeconds 28800

void initLEDs(){
    //TODO: Initialize the pin connected to the LEDs as outputs
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;

    //TODO: Turn each LED OF
    LATBbits.LATB12 = OFF;
    LATBbits.LATB13 = OFF;
    LATBbits.LATB14 = OFF;
    LATBbits.LATB15 = OFF;
}

void initSW1(){
    //TODO: Initialize the pin connected to the switch as an input.
    TRISBbits.TRISB5 = 1;
}


void initTimer1(){
    //TODO: Initialize the timer
    TMR1 = 0;
    PR1 = twoSeconds;
    IEC0bits.T1IE = 1; // Enable the interrupt
    T1CONbits.TCKPS = 0b11; //prescalar 256
    IFS0bits.T1IF = 0; // Timer 1 interrupt flag down
}