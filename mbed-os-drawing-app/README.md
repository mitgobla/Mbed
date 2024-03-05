# Drawing Application

This program allows you to control a cursor on the ILI9341 SPI TFT display using the joystick. Additionally, the buttons on the shield can be used to change the color, change the size of the cursor, and clear the canvas.

## Libraries

The SPI_TFT_ILI9341 library is originally from [https://os.mbed.com/teams/components/code/SPI_TFT_ILI9341/](https://os.mbed.com/teams/components/code/SPI_TFT_ILI9341/) however I have forked it to my [own repository](https://github.com/mitgobla/SPI_TFT_ILI9341/) and made some minor changes to the code to make it compatible with Mbed OS 6.

The LCD_Fonts library is from [https://os.mbed.com/users/dreschpe/code/LCD_fonts/](https://os.mbed.com/users/dreschpe/code/LCD_fonts/).

## Hardware Instructions

The pinout for the FRDM-K64F board can be found [here](https://os.mbed.com/platforms/FRDM-K64F/#arduino-and-nxp-header-pinout).

Documentation for the 2.8" TFT SPI screen module that I used can be found [here](http://www.lcdwiki.com/2.8inch_SPI_Module_ILI9341_SKU:MSP2807).

Information about the Joystick Shield 2.0 pinout can be found [here](https://electropeak.com/learn/interfacing-dual-axis-joystick-shield-with-arduino/).

### ILI9341 TFT Touchscreen

#### Display

1. Connect the **VCC** pin to a **3.3V** pin on the Joystick Shield.
2. Connect the **GND** pin to a **GND** pin on the Joystick Shield.
3. Connect the **CS** pin to the **D9** pin on the Joystick Shield.
4. Connect the **RESET** pin to the **D1/PTC17** pin on the FRDM-K64F board (happened to be the second to last pin on the Joystick Shield, above "E").
5. Connect the **DC** pin to the **D10** pin on the Joystick Shield.
6. Connect the **SDI/MOSI** pin to the **D11** pin on the Joystick Shield.
7. Connect the **SCK** pin to the **D13** pin on the Joystick Shield.
8. Connect the **LED** pin to a **3.3V** pin on the Joystick Shield.
9. Connect the **SDO/MISO** pin to the **D12** pin on the Joystick Shield.

#### Joystick Shield V2.0

Since this shield is designed for Arduino, it is directly compatible with the FRDM-K64F board. It connects to the outer pins on the board.

## Software Instructions

Not all the buttons on the Joystick Shield are used in this program. By default they are as follows:

- **E** - Clear Canvas
- **A** - Increase radius
- **C** - Decrease radius
- **B** - Next color
- **D** - Previous color

However, these can be changed in the `main.cpp` file. The button is mapped to an application function in the button map. The other buttons have been defined to `Button` objects so it is just the case of changing the relevant button to the desired function.
