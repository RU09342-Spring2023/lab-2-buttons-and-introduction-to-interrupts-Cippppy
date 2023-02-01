# Button Interrupt
Last lab you were introduced to the idea of "Polling" where in you would constantly check the status of the P1IN register to see if something has changed. While your code may have worked, it ends up spending a ton of time just checking something that has not changed. What we can do instead is use another two registers available to us from the GPIO peripheral, P1IE and P1IES, to allow our processor to just chill out and wait until something happens to act upon it. Without spending too much space on this README with explanations, what makes these interrupts tick is the following code:

```c
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
}
```

While you still need to initialize the Ports to be interrupt enabled and clear the flags, this "Pragma Vector" tells the compiler that when a particular interrupt occurs, run this code.

## Interrupts and Polling
### Polling
In the previous examples with the button, we have been using a technique called *polling* where you are constantly checking if the button is pressed or not. Polling works very well with the classic types of programing you have done in the past. For example, describing code as:
- Check the button state
- If button is pressed, do something
- Else if button is not pressed, do something else
- Do some other things and start over again
Every time we go through the loop, you are polling or checking the input pin state. This seems ok, but consider that you also have a _100ms delay_ in your loop for blinking the LEDs.

What happens if you press the button faster than 100ms, or something quick happens? You probably will miss the input, which is kinda the whole point of the code.

So then what can we do?

### Interrupts: "Tell me when the button is pressed"
Microcontrollers have the ability for the peripherals within them to generate an Interrupt Signal. Think of the processor as a teacher, and the peripherals as students. As the processor is teaching, it wants to know if anyone has a question it should stop and address. When **polling**, this is essentially as if the teacher points to each student and asks them if they have a question every so often. You could imagine that this is a lot of time possibly wasted, as there is a good chance at most, maybe a student might ask something.

**Interrupts** are like students raising their hands. Think about being in a classroom and having a question, what do you do? You raise your hand. The processor can then decide how it wants to _handle_ the interrupt. Should it stop immediately? Or do they need to finish a thought or sentence, then they can address the student.

From a code perspective, think about how that might change the previous flow with polling. Instead of constantly checking, we need to rethink a bit about how to approach this. So let's for now say that there is a _function_ that can be called every time the button gets pressed:
```c
// Global Variables
char buttonPressed = 0;
// Assume this is somehow able to run on its own when the button gets pressed.
void buttonPressedFunction(){
  if (theButtonIsPressed)
    buttonPressed = 1;
  else if (theButtonWasReleased)
    buttonPressed = 0;
}
```
This new function that runs each time the button is pressed sets a global variable that we can then use in our main loop to tell if the button has been pressed. This may not seem like we have done much, but take a look at the following.

```c
// Global Variables
char buttonPressed = 0;

while(1){
  if(buttonPressed)
    P1OUT ^= BIT0;
  else if (!buttonPressed)
    P6OUT ^= BIT6;
  __delay_cycles(100000);
}

// Runs each time the button is pressed
void buttonPressedFunction(){
  if (theButtonIsPressed)
    buttonPressed = 1;
  else if (theButtonWasReleased)
    buttonPressed = 0;
}

```
Now that we are allowing something else (the interrupt handler) to manage checking if the button is pressed, we actually **will not miss if the button is pressed**.

## Interrupt Handeling
Sitting right next to the CPU in your Microcontroller is a circuit which helps manage all of the interrupt signals from the peripherals in your microcontroller.

![Interrupt Prioritizer](https://gyazo.com/8b1680adafedd6082f7b4fb7b047e98d.png)

The INT signal is what allows your CPU to actually be told that there is an interrupt happening in a peripheral.

### Peripheral Generating an Interrupt

Interrupts start out in the peripheral itself. Using the GPIO peripheral as an example, let's look at how the interrupt is enabled and then sent to the processor.

![P1 Interrupt](https://i.gyazo.com/63c30393ec86ae4b84922ec10b623b97.png)

#### 1. The button needs to be an Input
To be able to watch a button, the Pin needs to be configured to an input. This is done as in previous examples simply by setting the correct pin in the Port DIRection register.
```c
P1DIR &= ~BIT1;
```
Now when the button is pressed either a 0 or a 1 can be brought into the peripheral.

#### 2. Enabling Inputs to be Generated
There are two main control signals that can be controlled. **P1IE** is the Interrupt Enable signal, and it is fed into an AND Gate. This means that if **P1IE** for that pin is set to a 0, _no interrupt signal can be generated_. If **P1IE** for that pin is set to a 1, then the output of the And gate will then be whatever comes out of the Latch.

**P1IES** controls an Edge Selection circuit, which will allow for an interrupt to be generated if the input transitions from a 0 to a 1, a 1 to a 0, or from either direction (rising or falling). The output of this edge selection circuit can control whether the latch is set or reset.

#### 3. Interrupt Being Generated
Now that the interrupts are configured and the edge selection is set, once the conditions are met, there are two places the signal from the latch goes to. The first place it to a **P1IFG** register. If you notice, the .x at the end means that there is one of these signals per bit in the port. This **P1IFG** register can be used to determine specifically which pin in the port had an interrupt generated, since technically multiple pins can have an interrupt at the same time.

The second is out of the And gate in out to the **P1 Interrupt** signal. This is what goes back towards the processor in order to let our program and CPU know something has happened. This goes into the *Interrupt Prioritizer* which was shown before.

### CPU Receives an Interrupt
Now that we have an interrupt generated, the CPU needs to handle it. First, the **GIE** General Interrupt Enable bit in the processor needs to be set before the interrupt happens so that it is actually able to be notified of the interrupt.

![Interrupt Handeling CPU](https://i.gyazo.com/6d797c228213079c569e93a2492b6d37.png)

Essentially:
- The CPU stops what it is doing, stores what instruction it was on.
- The CPU then loads in a **function pointer** which points to a routine or function to run when that specific interrupt happens.
- The CPU then runs that function.
- The last instruction in the function will be a return which will load the stack pointer and program counter back to the CPU and it will resume normal operations.

# Example Code - Part2.c
You will need to import and link the Part2.c file into your project for Lab 2, **AND MAKE SURE TO RIGHT CLICK ON PART1.c AND REMOVE FROM BUILD**. If you do not remove Part1.c from your build, you will get errors.

## Pragma Vector
Ok, what is going on here?
```c
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    ToggleEnable ^= 0x01;                   // Enable if the toggle should be active
}
```
First, **#pragma** is a compiler define, which basically means that the compiler is going to treat this as a special thing.

Second, **__interrupt void Port_2(void)**, the **__interrupt** is telling the compiler this function is actually an interrupt function. But let me make this clear, *this is itself a function!*. You are creating the function which needs to run whenever the interrupt condition happens. Formally, this is so that we can create a function pointer which allows the processor to actually point to the instructions for the function.

## Task
You will need to modify the code to make it where when the button is pressed it changes between the Red LED and Green LED that is blinking. You will have some TODO statements that will lead your towards the things that might need to be changed. You need to push an updated version of the code with the functionality.
