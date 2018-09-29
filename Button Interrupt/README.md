# Button Interrupt
This program allows the user to take control of the LED using a button on the board. For the MSP430G2553 implementation, the user is able to vary the blinking rate between various speeds by pressing the button.
## Methodology
The code utilizes the interrupt functions instead of relying on polling. This takes care of button bounce as well as making the code more efficient
## Dependencies
This code is dependent on the MSP430.h header file
