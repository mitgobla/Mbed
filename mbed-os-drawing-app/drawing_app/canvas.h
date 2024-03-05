// Represents a drawable area on the display, with a cursor position.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_CANVAS_H
#define MBED_CANVAS_H

#include "mbed.h"
#include "display.h"
#include "paintbrush.h"

class Canvas {
public:
    Canvas(Display& display, Paintbrush& paintbrush);

    unsigned int width();
    unsigned int height();
    void setBounds(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
    void moveCursorTo(unsigned int x, unsigned int y);
    void moveCursorBy(float x, float y);
    void draw();
    void clear();
private:
    Display& _display;
    Paintbrush& _paintbrush;

    unsigned int _cursorX;
    unsigned int _cursorY;
    unsigned int _x0;
    unsigned int _x1;
    unsigned int _y0;
    unsigned int _y1;
};

#endif