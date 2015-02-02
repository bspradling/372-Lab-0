// ******************************************************************************************* //
//
// File:         lab0.c
// Date:         
// Authors:      
//
// Description:  Lab 0 assignment for ECE 372 Spring 2015.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRI & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{
    //TODO: Define states by name
    firstLED, secondLED, thirdLED, fourthLED
} stateType;

typedef enum directionEnum{
    forward, backwards
}direction;

volatile stateType currentState = firstLED;
volatile direction ledDirection = forward;

int main(void)
{

    //TODO: Finish these functions in the provided c files
    initLEDs();
    initTimer1();
    initSW1();

    //Change Interrupt
    IEC1bits.CNIE = 1;
    IFS1bits.CNIF = 0;
    CNEN2bits.CN27IE = 1;

    while(1)
    {
        //Use a switch statement to define the behavior based on the state
        switch(currentState){
            case firstLED:
                turnOnLED(1);
                break;
            case secondLED:
                turnOnLED(2);
                break;
            case thirdLED:
                turnOnLED(3);
                break;
            case fourthLED:
                turnOnLED(4);
                break;
        }
    }
    return 0;
}


//Interrupts ------------------------------------------------------------


void _ISR _T1Interrupt(){
    IFS0bits.T1IF = 0; //Flag Down
    T1CONbits.TON = 0; //Timer Off

    ledDirection = backwards;
}

void _ISR _CNInterrupt(void){
    IFS1bits.CNIF = 0; //Flag Down

    if(PORTBbits.RB5 == 0){ //If Pressing Down
        buttonHeldDown();
    }
    else { //If Letting Go
        T1CONbits.TON = 0;
        determineCurrentLED();
    }
        
    
}

//-----------------------------------------------------------------------
//Helper Functions-------------------------------------------------------

void turnOnLED(int num){

    if (num == 1){ //turning on first LED
        LATBbits.LATB12 = OFF;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB15 = ON;
    }
    else if (num == 2){
        LATBbits.LATB12 = OFF;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB14 = ON;
        LATBbits.LATB15 = OFF;
    }
    else if (num == 3){
        LATBbits.LATB12 = OFF;
        LATBbits.LATB13 = ON;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB15 = OFF;
    }
    else if (num == 4){
        LATBbits.LATB12 = ON;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB15 = OFF;
    }

}

void buttonHeldDown(){
    T1CONbits.TON = 1; //Turn Timer On
    TMR1 = 0;  //Reset Count for Timer

    while (PORTBbits.RB5 == 0){ //While the Button is held down
        // wait for button to be let go
    }

}

void determineCurrentLED(){
    if (ledDirection == forward){ //Forward Direction
        if (currentState == firstLED)
            currentState = secondLED;
        else if (currentState == secondLED)
            currentState = thirdLED;
        else if (currentState == thirdLED)
            currentState = fourthLED;
        else if (currentState == fourthLED)
            currentState = firstLED;
    }
    else{  //Backward Direction
        if (currentState == firstLED)
            currentState = fourthLED;
        else if (currentState == secondLED)
            currentState = firstLED;
        else if (currentState == thirdLED)
            currentState = secondLED;
        else if (currentState == fourthLED)
            currentState = thirdLED;
    }

    ledDirection = forward; //reset forward direction
}

//--------------------------------------------------------------------