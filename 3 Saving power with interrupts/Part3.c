/*
 *  Energy Trace Example
 *
 *  Created on: Jan 30, 2023
 *      Author: Russell Trafford
 *      Version: 1.0
 *
 *      This example will show you the power consumption and energy consumption differences between polling and using an interrupt to turn on a processor.
 *
 *      Your task for this part of the lab is to capture two screenshots of the code running in Energy Trace, one with software polling, one with interrupts.
 *
 *      You will need to update the README for this part with the screenshots.
 */

#include <msp430.h>


void runCodeWithSoftwarePolling();
void runCodeWithInterrupts();

int main(){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //runCodeWithSoftwarePolling();

    runCodeWithInterrupts();

    return 0;
}

void runCodeWithSoftwarePolling(){

    P6DIR |= BIT6;              // Configure P6.6 to an Output
    P2DIR &= ~BIT3;             // Configure P2.3 to an Input

    P2REN |= BIT3;               // Enable Resistor on P2.3
    P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    while(1){
        if(P2IN & BIT3)
            P6OUT |= BIT6;
        else
            P6OUT &= ~BIT6;
    }
}

void runCodeWithInterrupts(){

    P6DIR |= BIT6;              // Configure P6.6 to an Output
    P2DIR &= ~BIT3;             // Configure P2.3 to an Input

    P2REN |= BIT3;               // Enable Resistor on P2.3
    P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

    P2REN |= BIT3;                          // P2.3 pull-up register enable
    P2IES &= ~BIT3;                         // P2.3 Low --> High edge
    P2IE |= BIT3;                           // P2.3 interrupt enabled

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    while(1){
        __bis_SR_register(LPM3_bits | GIE); // Enter LPM3 w/interrupt
        __no_operation();                   // For debug
        P6OUT ^= BIT6;                      // P6.6 = toggle
    }
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    P2IES ^= BIT3;                          // Transition the Edge Type (Low --> High, or High --> Low)
    __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}
