# Part 4: Occupancy Detection and Alert System
You are being asked to design a rudimentary occupancy alert system with the following behavior:
- The system when turned on needs to blink the Green LED once every 3 seconds to show it is armed.
- When the occupancy sensor detects someone, it will output a Logic 1, and your system needs to move into a "Warning" state, where the Green LED stops blinking, and the Red LED Blinks once per second (500ms on, 500ms off).
- If the occupancy detector still shows someone there after 10 seconds, your system should indicate this with the RED Led constantly staying on, and move into the ALERT state.
- If the occupancy detector **before** the 15 seconds goes back to a 0, indicating the room is now empty, then the system should go back to the armed state.
- When in the ALERT State, the only way for the system to go back to the Armed state is to press the P4.1 Button.

## Occupancy Sensor
You will be **first** *emulating* the Occupancy Sensor with the P4.1 button. This can be used for pretty much all of your testing and design.

When you have a design that is working, you can then test your code with a [Passive Infrared Occupancy Detector](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)

## Getting Started
I highly recommend on paper or a whiteboard drawing up a state machine or something to help understand the flow of the system.

From there, you should work on each stage/state and see if the transitions work. For example, can you get the system to go from the armed state to the warning state.

Remember that your code is going to be running in a loop, so you need to make sure you consider how this is going to work when trying to blink the LEDs.

## Do I need to use Interrupts?
Well, it would be cool, but at the end of the day, we are asking you for a design. Start with polling or what you feel comfortable with, but we would like you to try out using the interrupts, maybe at least for the system Disarm Button.

## Navigating multiple states
One way to approach a system with multiple states is to actually use a case statement in your main loop. For example:
```c
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here

char state = ARMED_STATE;

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
    }
    case WARNING_STATE:
    {
      // Do something in the WARNING_STATE
    }
  }
}
```

## Submission
There is a sample file in this folder you will need to import into your Code Composer and work on. You will need to submit that file, documented well, and a README.md file (you can replace this one) with the documentation that tells someone about what the code is, what it does, how it works etc. For an audience for your README, imagine you at the beginning of the lab, looking for code which does, well, this. 
