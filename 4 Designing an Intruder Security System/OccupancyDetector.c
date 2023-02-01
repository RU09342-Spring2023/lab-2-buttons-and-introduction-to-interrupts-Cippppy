/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: russty
 */

#include "GPIO_Driver.h"
#include <msp430.h>

#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

char Reset = 0x00;

char Motion = 0x00;

// Put some initialization here
int main (void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    char Timer = 0x00;

    gpioInit(1, 0, 1);
    gpioInit(6, 6, 1);

    gpioInit(2, 3, 0);
    P2IES &= ~BIT3;
    P2IE |= BIT3;
    P2IFG &= ~BIT3;

    gpioInit(3,6,0);
    P3IES &= ~BIT6;
    P3IE |= BIT6;
    P3IFG &= ~BIT6;

    gpioWrite(1,0,0);
    gpioWrite(6,6,0);

    __bis_SR_register(GIE);                 // Enter LPM3 w/interrupt

    char state = ARMED_STATE;

    while(1)
    {
      switch (state) {

        case ARMED_STATE:
        {
            Timer = 0x00;
            gpioWrite(1,0,0);

          // Do something in the ARMED state
          // If something happens, you can move into the WARNING_STATE
          // state = WARNING_STATE
            if (gpioRead(3,6)) {
                state = WARNING_STATE;
            }

            else{
                gpioWrite(6,6,1);
                __delay_cycles(500000);
                gpioWrite(6,6,0);
                __delay_cycles(3000000);
            }
        }

        case WARNING_STATE:
        {
            gpioWrite(6,6,0);
          // Do something in the WARNING_STATE
            if (gpioRead(2,3))
                state = ARMED_STATE;
            else if(Motion) {

                gpioWrite(1,0,1);
                __delay_cycles(500000);
                gpioWrite(1,0,0);
                __delay_cycles(500000);
                Timer = Timer + 1;

            }
            else
                state = ARMED_STATE;
        }

        case ALERT_STATE:
        {
            Timer = 0x00;
            gpioWrite(6,6,0);

            if (Reset)
                state = ARMED_STATE;
            else
                gpioWrite(1,0,1);
        }

      }
    }

    return 0;
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P2IFG &= ~BIT3;                         // Clear P2.3 IFG
    Reset ^= 0x01;                   // Enable if the toggle should be active
}


#pragma vector=PORT3_VECTOR
__interrupt void Port_3(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P3IFG &= ~BIT6;                         // Clear P2.3 IFG
    Motion ^= 0x01;                   // Enable if the toggle should be active
}

