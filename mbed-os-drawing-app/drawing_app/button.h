// Class representing a button. It simply stores a flag that the button has been pressed so that it can then be processed in the main thread.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_BUTTON_H
#define MBED_BUTTON_H

#include "mbed.h"
#include <mutex>

class Button {
public:
    Button(PinName buttonPin, bool rise = false);

    bool isTriggered();

private:
    InterruptIn _button;

    volatile bool _trigger;

    void trigger();
};

#endif