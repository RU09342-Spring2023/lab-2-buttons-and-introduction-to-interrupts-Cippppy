/*
 * OccupancyDetector.c
 *
 *  Created on: Feb 4, 2023
 *      Author: Christian Cipolletta
 */

#include "GPIO_Driver.h"
#include <msp430.h>

#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

void delay(unsigned int time) {     // Homemade delay function
    unsigned int i;
    for(i=0; i<time; i++) {
        __delay_cycles(1000);       // Delays by 0.001 seconds
    }
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    gpioInit(1,0,1);    // Set the red LED pin as output
    gpioWrite(1,0,0);   // Turn off the red LED

    gpioInit(6,6,1);    // Set the green LED pin as output
    gpioWrite(6,6,0);   // Turn off the green LED

    gpioInit(3,6,0);    // Set the occupancy sensor as input

    gpioInit(4,1,0);    // Set the button as input

    unsigned int counter = 0x00;           // Counter for 10 seconds in WARNING_STATE
    unsigned int motion_counter = 0x00;    // Counter because occupancy sensor has 5 second rest
    unsigned char state = ARMED_STATE;     // Default state

    while(1) {

        switch(state) {

            case ARMED_STATE:

                counter = 0;       // Resets 10 second counter
                gpioWrite(6,6,1);  // Turn on the green LED (Pin 6.6 to high)
                gpioWrite(1,0,0);  // Turn off red LED (Pin 1.0 to low)
                delay(500);

                gpioWrite(6,6,0); // Turn off the green LED (Pin 1.0 to low)
                delay(2500);

                if((gpioRead(3,6)) == 0) {      // If motion sensor is low (Pin 3.6 is low)
                    motion_counter++;
                }

                else {
                    motion_counter = 0;
                }

                if(gpioRead(3,6) != 0) {        // If motion sensor detects motion (Pin 3.6 is high)
                    state = WARNING_STATE;
                }
                break;

            case WARNING_STATE:

                gpioWrite(1,0,1);    // Turn on the red LED (Pin 1.0 to high)
                gpioWrite(6,6,0);    // Turn off the green LED (Pin 6.6 to low)
                delay(500);

                gpioWrite(1,0,0);   // Turn off the red LED (Pin 1.0 to high)
                delay(500);

                if(gpioRead(3,6) != 0) {        // If motion sensor detects motion (Pin 3.6 is high)
                    counter++;
                }

                if(counter == 3) {              // If 10 second timer is up
                    state = ALERT_STATE;
                }

                else if(gpioRead(3,6) == 0) {   // If motion sensor is low (Pin 3.6 is low)
                    motion_counter++;
                }

                else {
                    motion_counter = 0;
                }

                if(motion_counter == 5) {      // If 5 seconds go by and motion sensor is still low (Pin 3.6 is low)
                    state = ARMED_STATE;
                }
                break;

            case ALERT_STATE:

                gpioWrite(1,0,1);    // Turn on the red LED (Pin 1.0 is high)
                gpioWrite(6,6,0);    // Turn off the green LED (Pin 6.6 is low)

                if(gpioRead(4,1) == 0) {    // If button is pressed (4.1 is high)
                    state = ARMED_STATE;
                }
                break;
        }
    }
}
