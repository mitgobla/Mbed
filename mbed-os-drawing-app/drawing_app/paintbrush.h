// Class representing the paintbrush for the drawing canvas.
// Includes methods for the paintbrush color and radius
// Written by Ben Dodd (mitgobla)

#ifndef MBED_PAINTBRUSH_H
#define MBED_PAINTBRUSH_H

#include "mbed.h"
#include <mutex>
#include <array>
#include <string>

class Paintbrush {
public:

    Paintbrush();

    void increaseRadius();
    void decreaseRadius();
    int getRadius();

    void nextColor();
    void previousColor();
    unsigned short getColor();
    std::string getColorName();

private:
    int _radius;
    Mutex _radiusMutex;

    static const std::array<unsigned short, 7> _colorArray;
    static const std::array<std::string, 7> _colorNames;
    int _currentColor;
    Mutex _colorMutex;

};

#endif