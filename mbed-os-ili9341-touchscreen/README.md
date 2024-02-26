# ILI9341 SPI TFT Touchscreen Example

This program allows you to draw on the ILI9341 SPI TFT display using the stylus.

While drawing, the built-in LED on the FRDM-K64F board will light green. Pressing the **SW3** button will clear the canvas.

## Libraries

The SPI_TFT_ILI9341 library is originally from [https://os.mbed.com/teams/components/code/SPI_TFT_ILI9341/](https://os.mbed.com/teams/components/code/SPI_TFT_ILI9341/) however I have forked it to my [own repository](https://github.com/mitgobla/SPI_TFT_ILI9341/) and made some minor changes to the code to make it compatible with Mbed OS 6.

The UTouch library is from [https://os.mbed.com/users/rpocc/code/UTouch/](https://os.mbed.com/users/rpocc/code/UTouch/).

The LCD_Fonts library is from [https://os.mbed.com/users/dreschpe/code/LCD_fonts/](https://os.mbed.com/users/dreschpe/code/LCD_fonts/).

## Hardware Instructions

The pinout for the FRDM-K64F board can be found [here](https://os.mbed.com/platforms/FRDM-K64F/#arduino-and-nxp-header-pinout).

Documentation for the 2.8" TFT SPI screen module that I used can be found [here](http://www.lcdwiki.com/2.8inch_SPI_Module_ILI9341_SKU:MSP2807).

### ILI9341 TFT Touchscreen

#### Display

1. Connect the **VCC** pin to a **3.3V** pin on the FRDM-K64F board.
2. Connect the **GND** pin to a **GND** pin on the FRDM-K64F board.
3. Connect the **CS** pin to the **D7/PTC3** pin on the FRDM-K64F board.
4. Connect the **RESET** pin to the **D6/PTC2** pin on the FRDM-K64F board.
5. Connect the **DC** pin to the **D5/PTA2** pin on the FRDM-K64F board.
6. Connect the **SDI/MOSI** pin to the **D11/PTD2** pin on the FRDM-K64F board.
7. Connect the **SCK** pin to the **D13/PTD1** pin on the FRDM-K64F board.
8. Connect the **LED** pin to a **3.3V** pin on the FRDM-K64F board.
9. Connect the **SDO/MISO** pin to the **D12/PTD3** pin on the FRDM-K64F board.

#### Touchscreen

1. Connect the **T_IRQ** pin to the **D0/PTC16** pin on the FRDM-K64F board.
2. Connect the **T_CS** pin to the **D3/PTA1** pin on the FRDM-K64F board.
3. Connect the **T_SCK** pin to the **D4/PTB23** pin on the FRDM-K64F board.
4. Connect the **T_DIN** pin to the **D2/PTB9** pin on the FRDM-K64F board.
5. Connect the **T_DO** pin to the **D1/PTC17** pin on the FRDM-K64F board.

### LED

This program uses the built-in LED on the FRDM-K64F board, which uses pin **LED1/PTB22**, **LED2/PTE26**, **LED3/PTB21**.

You could modify the pins of `red_led` and `green_led` to use other digital pins for an external RGB LED.

### Button

This program uses the built-in button on the FRDM-K64F board, which uses pin **SW3/PTA4**.
