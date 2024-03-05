// Class that stores buttons and binds them to a specific function
// Written by Ben Dodd (mitgobla)

#ifndef MBED_BUTTONMAP_H
#define MBED_BUTTONMAP_H

#include "mbed.h"
#include "button.h"
#include "map"

enum ApplicationButtonType {
    CLEAR_CANVAS_BUTTON,
    NEXT_COLOR_BUTTON,
    PREV_COLOR_BUTTON,
    INCREASE_RADIUS_BUTTON,
    DECREASE_RADIUS_BUTTON
};

class ButtonMap {
public:
    ButtonMap();
    void addButton(ApplicationButtonType type, Button* button);
    Button* getButton(ApplicationButtonType type);
private:
    std::map<ApplicationButtonType, Button*> _buttons;
};

#endif