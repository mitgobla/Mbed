// Class representing the paintbrush for the drawing canvas.
// Includes methods for the paintbrush color and radius
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "paintbrush.h"
#include <mutex>
#include <array>
#include <string>
#include "SPI_TFT_ILI9341.h"

const std::array<unsigned short, 7> Paintbrush::_colorArray = {White, Red, Green, Blue, Magenta, Yellow, Cyan};
const std::array<string, 7> Paintbrush::_colorNames = {"White", "Red", "Green", "Blue", "Magenta", "Yellow", "Cyan"};

Paintbrush::Paintbrush() : _currentColor(0), _radius(1) {};

// Increase the radius of the brush.
// Radius is between 1 and 10
void Paintbrush::increaseRadius() {
    _radiusMutex.lock();
    _radius = _radius < 10 ? _radius + 1 : _radius;
    _radiusMutex.unlock();
}

// Decrease the radius of the brush.
// Radius is between 1 and 10
void Paintbrush::decreaseRadius() {
    _radiusMutex.lock();
    _radius = _radius > 1 ? _radius - 1 : _radius;
    _radiusMutex.unlock();
}

// Get the radius of the brush.
// Radius is between 1 and 10
int Paintbrush::getRadius() {
    _radiusMutex.lock();
    int radius = _radius;
    _radiusMutex.unlock();
    return radius;
}

// Select the next color index
// Wraps to start of array if increments out of range of the array.
void Paintbrush::nextColor() {
    _colorMutex.lock();
    _currentColor = (_currentColor + 1) % _colorArray.size();
    _colorMutex.unlock();
}

// Select the previous color index
// Wraps to end of array if decrements out of range of the array.
void Paintbrush::previousColor() {
    _colorMutex.lock();
    _currentColor = (_currentColor - 1 + _colorArray.size()) % _colorArray.size();
    _colorMutex.unlock();
}

// Get the short color code of the current color
unsigned short Paintbrush::getColor() {
    _colorMutex.lock();
    unsigned short color = _colorArray[_currentColor];
    _colorMutex.unlock();
    return color;
}

// Get the name of the current color
std::string Paintbrush::getColorName() {
    _colorMutex.lock();
    std::string color = _colorNames[_currentColor];
    _colorMutex.unlock();
    return color;
}

