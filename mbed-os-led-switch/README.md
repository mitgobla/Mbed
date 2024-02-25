# Basic LED Switch Example

This program lights up the built-in LED on the FRDM-K64F board when a button is pressed.

Pressing SW2 will go to the next colour, and pressing SW3 will go to the previous colour.

Since the LED does not support PWM, the colours are represented by a binary number, where each bit represents a colour. The colours are as follows:

- 0b000: Off
- 0b001: Red
- 0b010: Green
- 0b100: Blue
- 0b011: Yellow
- 0b101: Cyan
- 0b110: Magenta
- 0b111: White

When the colour changes, the new colour is output to serial.

## Hardware Instructions

No additional hardware is needed. The FRDM-K64F board has a built-in LED and buttons.

## Software Instructions

Make sure you have the microcontroller setup to send serial output to your computer. I use PuTTY to read the serial output.
