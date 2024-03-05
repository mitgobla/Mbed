#include "mbed.h"
#include "drawapplication.h"

// VCC
// GND
// CS		    D9
// RESET	    D1
// DC		    D10
// SDI(MOSI)	MOSI-D11
// SCK		    SCK-D13
// LED
// SDO(MISO)	MISO-D12

// TFT LCD Display
PinName csPin(ARDUINO_UNO_D9);
PinName resetPin(ARDUINO_UNO_D1);
PinName dcPin(ARDUINO_UNO_D10);
PinName mosiPin(ARDUINO_UNO_D11);
PinName sckPin(ARDUINO_UNO_D13);
PinName misoPin(ARDUINO_UNO_D12);

Display display(mosiPin, misoPin, sckPin, csPin, resetPin, dcPin);

// Joystick Shield
PinName joyX(ARDUINO_UNO_A0);
PinName joyY(ARDUINO_UNO_A1);

Joystick joystick(joyX, joyY);

Button joyK(ARDUINO_UNO_D8);
Button btA(ARDUINO_UNO_D2);
Button btB(ARDUINO_UNO_D3);
Button btC(ARDUINO_UNO_D4);
Button btD(ARDUINO_UNO_D5);
Button btE(ARDUINO_UNO_D6);
Button btF(ARDUINO_UNO_D7);

ButtonMap buttonMap;

DrawApplication drawApplication(display, joystick, buttonMap);

// main() runs in its own thread in the OS
int main()
{
    buttonMap.addButton(CLEAR_CANVAS_BUTTON, &btE);
    buttonMap.addButton(INCREASE_RADIUS_BUTTON, &btA);
    buttonMap.addButton(DECREASE_RADIUS_BUTTON, &btC);
    buttonMap.addButton(NEXT_COLOR_BUTTON, &btB);
    buttonMap.addButton(PREV_COLOR_BUTTON, &btD);
    drawApplication.run();
}
