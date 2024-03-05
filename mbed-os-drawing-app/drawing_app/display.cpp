// Class that represents the SPI_TFT_ILI9341 display and functions for the drawing application
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "Arial12x12.h"
#include "display.h"
#include <string>

const int Display::ORIENTATION = 1;
const unsigned char* Display::FONT = Arial12x12;
const unsigned int Display::BACKGROUND = Black;
const unsigned int Display::FOREGROUND = White;

Display::Display(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc)
    : SPI_TFT_ILI9341(mosi, miso, sclk, cs, reset, dc) {};

// Run before the main loop of the program to setup the display.
void Display::setup() {
    set_orientation(ORIENTATION);
    foreground(FOREGROUND);
    background(BACKGROUND);
    set_font((unsigned char*) FONT);
    cls();
};

// Write text onto the display.
// By default, the position is at 0, 0.
void Display::writeText(std::string text, int x, int y) {
    int padding = columns() - text.length();
    if (padding > 0) {
        text.append(padding + 2, ' ');
    }
    locate(x, y);
    printf("%s", text.c_str());
};

// Draw the paintbrush at the specified coordinates.
void Display::draw(int x, int y, Paintbrush& brush) {
    fillcircle(x, y, brush.getRadius(), brush.getColor());
};
