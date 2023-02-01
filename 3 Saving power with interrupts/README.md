# Saving and Measuring Power on your Microcontroller
While plugged into your computer or a charger, the power consumption of your device might not be of utmost importance, but many systems are seeking for low power consumption. To get this discussion started, we are going to take a look at two different pieces of code to simply turn an LED on when a button is pressed. But we will see that one method keeping the CPU on consumes much more power than when we can turn them off. This will be monitored using Energy Trace which is built in to the Code Composer IDE.

## What is our processor actually doing?

Let's take a look at the simple software polling example which will cause an LED to turn on whenever we hold the button down.

```c
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
```
In this example, the CPU itself is spending all of its time running that loop. That means all 1MHz is going into just checking to see if the button is pressed. This works, and honestly, if power isnt a problem, then it is actually an ok solution.

### Task: Power Consumption

Import the Part3.c code into your project, and comment out the "runCodeWithInterrupts()" function. Make sure the "runCodeWithPolling()" function is uncommented. Run the code and see how it works. Then, remove the J11 Jumper connecting the LED to the Microcontroller, and run Energy Trace to see how the power consumption of the microcontroller is impacted when you are pressing the button.

## Using Interrupts
If we look at an example based around using an interrupt, we can see an interesting thing happening.

```c
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

...

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    P2IES ^= BIT3;                          // Transition the Edge Type (Low --> High, or High --> Low)
    __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}
```

In the while() loop, the first thing we do is **turn the CPU Off!** Yeah. We literally are telling this thing to enter a power mode where the actual Processor/CPU is not getting power. So how does this work then? We also set **GIE** which is the Global Interrupt Enable. So basically, we are telling our CPU to go to sleep until the button is pressed.

When the button is pressed, the interrupt vector is fired and the CPU wakes up, runs the code in the interrupt routine, and the we tell the CPU to kick back on. It will then resume the code in the While() loop until we hit that LPM3_bits line, and then it sleeps again.

### Task: Power Consumption of the Interrupts
Run the code in Part3.c, but this time uncomment the runCodeWithInterrupts() function, while commenting out the runCodeWithPolling line. See how the device works and see if you can use breakpoints to catch the code when you are pressing the button.

Then load up Energy Trace and perform the similar capture of Power with the LED Jumper taken off. Compare the two graphs and see if you can explain two things:
1. What is causing the bias/baseline in the polling example to be higher than the interrupt example.
2. Even with the LED unplugged, why is there still power increases when you press the button?


# Screenshots and Answers to Questions
**Replace this section with your screenshots of Energy Trace and provide some reasoning as to Questions 1 and 2 in the Power consumption of the Interrupts Section.**
