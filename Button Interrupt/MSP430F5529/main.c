
//Taken from: http://processors.wiki.ti.com/index.php/MSP430_LaunchPad_PushButton
//comments have been modified

//David Sheppard
//16 September 2018
//Lab 1: Button Blink for MSP430G2553
//Allows user to control 2 LEDs using the pin 3 button
//LEDs are on when button is held down, off when button is not held
//This uses the interrupt method

#include <msp430.h>

#define LED1 BIT0   //defining LED1 as BIT6
#define BUTTON BIT1 //defining BUTTON as BIT3

int speed;

int main(void)  //begin main function
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    P1DIR |= (LED1);     // Set P1.0 (LED) to be an output

    P1OUT &= ~LED1;             // shut off LED0
    P1IE |= BUTTON;             // enable P1.3 interrupt

    P1IFG &= ~BUTTON;           // clear the P1.3 interrupt flag

    __enable_interrupt();       // enable interrupts

    speed = 0;

    while(1){

    while(speed == 0){      //low speed
        P1OUT ^= LED1;
        __delay_cycles(500000);
    }

    while(speed == 1){      //medium speed
        P1OUT ^= LED1;
        __delay_cycles(250000);
    }

    while(speed == 2){      //high speed
        P1OUT ^= LED1;
        __delay_cycles(125000);
    }

    }

}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)   //take care of interrupt coming from port 1
{

P1IFG &= ~BUTTON;               // clear the P1.3 interrupt flag
P1IES ^= BUTTON;                // toggle the interrupt edge,
if(P1IES == 0){                 //want this to happen only on falling edge of button
    if(speed != 2)
        speed++;
    else if(speed == 2)
        speed = 0;
    else speed = 0; //should never execute, but just in case
}
// the interrupt vector will be called
// when P1.3 goes from HitoLow as well as
// LowtoHigh
}
