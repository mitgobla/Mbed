// Drawing application, that utilizes a joystick for drawing a paintbrush, and buttons for various actions.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_DRAWAPPLICATION_H
#define MBED_DRAWAPPLICATION_H

#include "mbed.h"
#include "display.h"
#include "joystick.h"
#include "buttonmap.h"
#include "canvas.h"
#include <string>

class DrawApplication {
public:
    DrawApplication(Display& display, Joystick& joystick, ButtonMap& buttonMap);

    void run();
private:
    Display& _display;
    Joystick& _joystick;
    ButtonMap& _buttonMap;
    Paintbrush _paintbrush;
    Canvas _canvas;

    bool isButtonPressed(ApplicationButtonType type);
    void clearCanvas();
    void setup();
    void updateInformationText();
};

#endif