// Class representing a button. It simply stores a flag that the button has been pressed so that it can then be processed in the main thread.
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "button.h"

// Represents a button. Optional boolean to specify if the button is triggered on rise instead of fall.
Button::Button(PinName buttonPin, bool rise) : _button(buttonPin) {
    _trigger = false;
    if (rise) {
        _button.rise([&] {this->trigger();});
    } else {
        _button.fall([&] {this->trigger();});
    }
};

// Return if the button has been triggered or not.
// The trigger is reset after checking.
bool Button::isTriggered() {
    bool trigger = _trigger;
    _trigger = false;
    return trigger;
}


// Set the button to be triggered.
void Button::trigger() {
    _trigger = true;
}

