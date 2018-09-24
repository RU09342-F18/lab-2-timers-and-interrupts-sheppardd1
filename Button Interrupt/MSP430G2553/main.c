
//Taken from: http://processors.wiki.ti.com/index.php/MSP430_LaunchPad_PushButton
//comments have been modified

//David Sheppard
//16 September 2018
//Lab 1: Button Blink for MSP430G2553
//Allows user to control 2 LEDs using the pin 3 button
//LEDs are on when button is held down, off when button is not held
//This uses the interrupt method

#include <msp430G2553.h>

#define LED0 BIT0   //defining LED0 as BIT0
#define LED1 BIT6   //defining LED1 as BIT6
#define BUTTON BIT3 //defining BUTTON as BIT3


int main(void)  //begin main function
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    P1DIR |= (LED0 + LED1);     // Set P1.0 (LED) to be an output

    P1OUT &= ~LED0;             // shut off LED0
    P1IE |= BUTTON;             // enable P1.3 interrupt

    P1IFG &= ~BUTTON;           // clear the P1.3 interrupt flag

    __enable_interrupt();       // enable interrupts

}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)   //take care of interrupt coming from port 1
{
P1OUT ^= (LED0 + LED1);         // P1.0 gets toggled
P1IFG &= ~BUTTON;               // clear the P1.3 interrupt flag
P1IES ^= BUTTON;                // toggle the interrupt edge,
// the interrupt vector will be called
// when P1.3 goes from HitoLow as well as
// LowtoHigh
}
