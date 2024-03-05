// Class that represents the SPI_TFT_ILI9341 display and functions for the drawing application
// Written by Ben Dodd (mitgobla)

#ifndef MBED_DISPLAY_H
#define MBED_DISPLAY_H

#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "paintbrush.h"
#include <string>

class Display : public SPI_TFT_ILI9341 {
public:
    Display(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset, PinName dc);

    void setup();
    void writeText(std::string text, int x = 0, int y = 0);
    void draw(int x, int y, Paintbrush& brush);
private:
    static const int ORIENTATION;
    static const unsigned char* FONT;
    static const unsigned int FOREGROUND;
    static const unsigned int BACKGROUND;
};

#endif