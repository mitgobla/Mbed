// Class that stores buttons and binds them to a specific function
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "buttonmap.h"
#include <stdexcept>

ButtonMap::ButtonMap() {};

// Add a pointer to a button to the mapping, bound to a specific function type
void ButtonMap::addButton(ApplicationButtonType type, Button* button) {
    _buttons[type] = button;
};

// Get a pointer to a button from the mapping for a specific function type
// Returns nullptr if the button was not found.
Button* ButtonMap::getButton(ApplicationButtonType type) {
    if (_buttons.count(type) > 0) {
        return _buttons[type];
    } else {
        return nullptr;
    }
}