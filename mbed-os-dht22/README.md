# DHT22 Example

This program reads the temperature and humidity from a DHT22 sensor and outputs the values to serial.
Additionally, it will set the colour of the LED on the FRDM-K64F board depending on a range of temperatures, shown below.
When the temperature is in the high range, the buzzer will sound every 5 seconds.

## Libraries

The DHT22 library is from [https://os.mbed.com/teams/Thing-Innovations/code/DHT/](https://os.mbed.com/teams/Thing-Innovations/code/DHT/)

However the code contains depreciated usage of `wait_ms` which I have modified to use `ThisThread::sleep_for`. This is so this program can be compiled with Mbed OS 6.

## Hardware Instructions

The pinout for the FRDM-K64F board can be found [here](https://os.mbed.com/platforms/FRDM-K64F/#arduino-and-nxp-header-pinout).

### DHT22 sensor

1. Connect the **VCC** pin to the **5V** pin on the FRDM-K64F board.
2. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
3. Connect the **SIG/OUT** pin to the **D2/PTB9** pin on the FRDM-K64F board.

### Buzzer

1. Connect the **VCC** pin to the **5V** pin on the FRDM-K64F board.
2. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
3. Connect the **SIG** pin to the **D3/PTA1** (PWM) pin on the FRDM-K64F board.

### LED

This program uses the built-in LED on the FRDM-K64F board, which uses pin **LED1/PTB22**, **LED2/PTE26**, **LED3/PTB21**.

You could modify the array of `DigitalOut` to use other digital pins for an RGB LED.
