// Basic LED library to control the LED colors on the FRDM-K64F board.
// Written by Ben Dodd (mitgobla)

#include "LED.h"
#include <array>

LED::LED(std::array<DigitalOut, 3>& leds) : _leds(leds) {
    _color = OFF;
    setColor(_color);
}

LED::~LED() {}

void LED::setColor(eColor color) {
    _color = color;
    for (int i = 0; i < 3; i++) {
        _leds[i] = (_color & (1 << i)) ? 0 : 1;
    }
}