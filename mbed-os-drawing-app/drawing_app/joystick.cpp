// Class representing the joystick on the Joystick Shield board.
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "joystick.h"

Joystick::Joystick(PinName joyX, PinName joyY, float deadzone)
    : _joyX(joyX), _joyY(joyY), _deadzone(deadzone), _restX(0.0), _restY(0.0) {};

// Set the resting positions to the current readings.
// Run this at the start of the code. Don't touch the joystick otherwise the calibration may be wrong.
void Joystick::calibrate() {
    _restX = _joyX.read();
    _restY = _joyY.read();
}

// Remap a value with a rest (middle) point to be between -1.0 and 1.0
float Joystick::remap(float value, float rest) {
    if (value <= rest) {
        return (value - rest) / rest;
    } else {
        return (value - rest) / (1.0 - rest);
    }
}

// Read the value, mapped between -1.0 and 1.0
// If the value is within the deadzone around 0.0, then 0.0 is returned.
float Joystick::read(float value, float rest) {
    float reading = remap(value, rest);
    if (abs(reading) > _deadzone) {
        return reading;
    }
    return 0.0;
};

// Read the value of X, mapped between -1.0 and 1.0
// 0.0 is considered the middle point, which is the resting position when calibrated.
float Joystick::readX() {
    return read(_joyX.read(), _restX);
}

// Read the value of Y, mapped between -1.0 and 1.0
// 0.0 is considered the middle point, which is the resting position when calibrated.
float Joystick::readY() {
    return read(_joyY.read(), _restY);
}

// Invert the value.
// Reads more clearly to invert a joystick axis.
float Joystick::invert(float value) {
    return value * -1.0;
}