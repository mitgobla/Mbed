# Ultrasonic Sensor Example

This program reads the distance from an ultrasonic sensor, and interpolates the distance to red and green values. The red and green values are then output to an externally connected RGB LED on the FRDM-K64F board.

## Hardware Instructions

The pinout for the FRDM-K64F board can be found [here](https://os.mbed.com/platforms/FRDM-K64F/#arduino-and-nxp-header-pinout).

### Ultrasonic Sensor

1. Connect the **VCC** pin to the **5V** pin on the FRDM-K64F board.
2. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
3. Connect the **TRIG** pin to the **D8/PTC12** pin on the FRDM-K64F board.
4. Connect the **ECHO** pin to the **D9/PTC4** pin on the FRDM-K64F board.

### RGB LED

1. Connect the **R** pin to the **D5/PTA2** (PWM) pin on the FRDM-K64F board.
2. Connect the **G** pin to the **D6/PTC2** (PWM) pin on the FRDM-K64F board.
3. **B** pin is not used.
4. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
