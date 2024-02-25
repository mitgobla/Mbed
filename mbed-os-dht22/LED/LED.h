// Basic LED library to control the LED colors on the FRDM-K64F board.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_LED_H
#define MBED_LED_H

#include "mbed.h"
#include <array>

typedef enum {
    OFF = 0b000,
    RED = 0b001,
    GREEN = 0b010,
    BLUE = 0b100,
    YELLOW = 0b110,
    CYAN = 0b110,
    PURPLE = 0b101,
    WHITE = 0b111
} eColor;

class LED {
public:
    LED(std::array<DigitalOut, 3>& leds);
    ~LED();

    void setColor(eColor color);

private:
    std::array<DigitalOut, 3> _leds;
    eColor _color;

};

#endif