# RGB LED Example

This program cycles through the colours of an external RGB LED, connected to the FRDM-K64F board in its PWM pins.

Each colour is increased from 0 to 1 with a random delay between 0 and 0.5 seconds. Then the colour is decreased from 1 to 0 with a random delay between 0 and 0.5 seconds.

Since there are three colours, three threads are used to control each colour.

## Hardware Instructions

The pinout for the FRDM-K64F board can be found [here](https://os.mbed.com/platforms/FRDM-K64F/#arduino-and-nxp-header-pinout).

### RGB LED

1. Connect the **R** pin to the **D5/PTA2** (PWM) pin on the FRDM-K64F board.
2. Connect the **G** pin to the **D6/PTC2** (PWM) pin on the FRDM-K64F board.
3. Connect the **B** pin to the **D7/PTC3** (PWM) pin on the FRDM-K64F board.
4. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
