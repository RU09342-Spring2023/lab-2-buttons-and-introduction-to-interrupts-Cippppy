# Buttons and Pullup/Pulldown Resistors
- [ ] 1. Read up on Pullup and Pulldown Resistors
- [ ] 2. Import and Link the Part1.c file into Code Composer
- [ ] 3. **Deliverable TASK:** Modify the Part1.c file to make the LEDS Toggle/Blink when the buttons are pressed only

## Buttons and Floating Inputs
For reasons, the buttons on your launchpad have been left as a simple button connected to ground with no pull up resistor. This will lead you to have issues trying to use them. This is a summary of why you are probably having issues, and the ways around getting the buttons to work (note, they are not broken).

## What is on your board?
Looking at the [Launchpad Datasheet](https://www.ti.com/lit/ug/slau680/slau680.pdf?ts=1674790902969&ref_url=https%253A%252F%252Fwww.google.com%252F), you can scroll down to the schematic and find that the buttons are in fact just hooked into ground and then into the microcontroller. This seems like an odd thing to do, and will cause you to have floating inputs (where the pin is never actually being told what voltage to be at, hence when you are touching the pin or button, it will sometimes flip between a one or zero).

![Button Schematic](https://i.gyazo.com/678b2b3c1788134372efa4530e1a1f13.png)

## Internal pull-up resistor
Inside of each one of the pins, there is a circuit which can be enabled to allow a resistor to be put in parallel with the pin and ground or Vcc.
![Pullup Resistor](https://i.gyazo.com/dccdf72d0c59fb83d662d86280db6f5e.png)
This is actually really helpful and will come in handy later in the course as well. But for now, we can configure the hardware to allow us to connect a resistor from the switch pin to Vcc. This will allow the button to register a 0 when connected to ground, and then "pull up" the pin to a 1 (Vcc) when the switch is an open circuit.

##How to enable this internal resistor
You could either work through the diagram, or, if you search on the [Family User Guide](https://www.ti.com/lit/ug/slau445i/slau445i.pdf?ts=1674790523141&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FMSP430FR2355) for "PXREN" [The "X" is the general place holder], you can see a table which will tell you how to configure the pin as an "Input with Pull Up Resistor"
!(Internal Pullup Settings)[https://i.gyazo.com/643ecba26d0e5bcf7fdaf977d318d385.png]

# Part 1 Deliverable
You will need to import/link this file into Code Composer and run it, see how it functions. You then need to modify such that the buttons will cause the buttons to blink when they are held down.
## Submitting
If you link this file to code composer, GitKraken will be tracking the file and you will be able to Commit and Push with no issue.
## Advice
I would suggest taking a look with the Debugger at what the **P1IN** register looks like when you are pressing the button, and determine how your code should be changed around what you find.
