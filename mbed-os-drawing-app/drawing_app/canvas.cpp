// Represents a drawable area on the display, with a cursor position.
// Written by Ben Dodd (mitgobla)

#include "canvas.h"
#include "display.h"
#include "mbed.h"
#include "paintbrush.h"
#include <cstdio>


Canvas::Canvas(Display &display, Paintbrush &paintbrush)
    : _display(display), _paintbrush(paintbrush) {};

unsigned int Canvas::width() {
    return _x1 - _x0;
}

unsigned int Canvas::height() {
    return _y1 - _y0;
}

// Set the bounding area of the canvas.
// x0, y0 - top left corner
// x1, y1 - bottom right corner
void Canvas::setBounds(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) {
    _x0 = x0;
    _y0 = y0;
    _x1 = x1 > _display.width() ? _display.width() : x1;
    _y1 = y1 > _display.height() ? _display.height() : y1;
}

// Move the cursor to a position on the canvas.
// 0,0 is the top left of the canvas, not the display.
void Canvas::moveCursorTo(unsigned int x, unsigned int y) {
    unsigned int brushOffset = _paintbrush.getRadius();
    if (x < brushOffset) {
        _cursorX = brushOffset;
    } else if (x > width() - brushOffset) {
        _cursorX = width() - brushOffset;
    } else {
        _cursorX = x;
    }

    if (y < brushOffset) {
        _cursorY = brushOffset;
    } else if (y > height() - brushOffset) {
        _cursorY = height() - brushOffset;
    } else {
        _cursorY = y;
    }
};


// Move the cursor by the specified amount in the x and y direction.
void Canvas::moveCursorBy(float x, float y) {
    int newX = _cursorX + static_cast<int>(round(x));
    int newY = _cursorY + static_cast<int>(round(y));
    moveCursorTo(newX >= 0 ? newX : 0, newY >= 0 ? newY : 0);
};

// Draw on the canvas at the cursor position using the assigned paintbrush
void Canvas::draw() {
    _display.draw(_x0 + _cursorX, _y0 + _cursorY, _paintbrush);
};

// Clear the drawing area of the canvas
void Canvas::clear() {
    _display.fillrect(_x0, _y0, _x1, _y1, Black);
};