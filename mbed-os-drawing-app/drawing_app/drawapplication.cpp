// Drawing application, that utilizes a joystick for drawing a paintbrush, and buttons for various actions.
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "drawapplication.h"
#include "display.h"
#include "joystick.h"
#include "buttonmap.h"
#include "canvas.h"
#include <string>

DrawApplication::DrawApplication(Display& display, Joystick& joystick, ButtonMap& buttonMap) : 
    _display(display),
    _joystick(joystick), 
    _buttonMap(buttonMap), 
    _paintbrush(),
    _canvas(_display, _paintbrush) {};

// Check if a button for a specific application action has been pressed.
bool DrawApplication::isButtonPressed(ApplicationButtonType type) {
    if (_buttonMap.getButton(type) != nullptr) {
        return _buttonMap.getButton(type)->isTriggered();
    }
    return false;
};

// Clear the canvas and reset the cursor back to the middle
void DrawApplication::clearCanvas() {
    _display.writeText("Clearing Canvas...", 4, 4);
    _canvas.clear();
    _canvas.moveCursorTo(_canvas.width() / 2, _canvas.height() / 2);
    updateInformationText();
};

// Run before main loop, this runs all setup functions
// of components and the canvas.
void DrawApplication::setup() {
    _joystick.calibrate();
    _display.setup();
    _canvas.setBounds(0, 19, _display.width(), _display.height());
    clearCanvas();
};

// Update the text displayed at the top of the canvas
void DrawApplication::updateInformationText() {
    string text = "Radius: " + to_string(_paintbrush.getRadius()) + "    Color: " + _paintbrush.getColorName();
    _display.writeText(text, 4, 4);
    _display.line(0, 18, _display.width(), 18, White);
};

void DrawApplication::run() {
    setup();
    while (true) {
        // Draw when joystick is moved
        float joystickX = _joystick.readX();
        float joystickY = _joystick.invert(_joystick.readY());
        if (joystickX != 0 || joystickY != 0) {
            _canvas.moveCursorBy(joystickX, joystickY);
            _canvas.draw();
        }

        // Button Presses
        // Clear canvas
        if (isButtonPressed(CLEAR_CANVAS_BUTTON)) {
            clearCanvas();
        }

        // Decrease brush radius
        if (isButtonPressed(DECREASE_RADIUS_BUTTON)) {
            _paintbrush.decreaseRadius();
            updateInformationText();
        }

        // Increase brush radius
        if (isButtonPressed(INCREASE_RADIUS_BUTTON)) {
            _paintbrush.increaseRadius();
            updateInformationText();
        }

        // Previous color
        if (isButtonPressed(PREV_COLOR_BUTTON)) {
            _paintbrush.previousColor();
            updateInformationText();
        }

        // Next color
        if (isButtonPressed(NEXT_COLOR_BUTTON)) {
            _paintbrush.nextColor();
            updateInformationText();
        }

        // Sleep for CPU
        ThisThread::sleep_for(50ms);
    }
};