// Library to recieve data from an ultrasonic sensor.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_ULTRASONIC_H
#define MBED_ULTRASONIC_H

#include "mbed.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(PinName trigPin, PinName echoPin);
    ~UltrasonicSensor();

    float readDistance();
private:
    DigitalOut _trigPin;
    InterruptIn _echoPin;
    Timer _timer;
    volatile int _duration;

    void triggerSensor();
    void echoStart();
    void echoEnd();
};

#endif