// Class representing the joystick on the Joystick Shield board.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_JOYSTICK_H
#define MBED_JOYSTICK_H

#include "mbed.h"

class Joystick {
public:
    Joystick(PinName joyX, PinName joyY, float deadzone = 0.1);

    void calibrate();
    float readX(); 
    float readY();
    static float invert(float value);

private:
    AnalogIn _joyX;
    AnalogIn _joyY;

    float _restX;
    float _restY;
    float _deadzone;

    float read(float value, float rest);
    float remap(float value, float middle);

};

#endif