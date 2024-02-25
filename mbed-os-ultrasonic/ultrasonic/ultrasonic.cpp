// Library to recieve data from an ultrasonic sensor.
// Written by Ben Dodd (mitgobla)

#include "ultrasonic.h"

UltrasonicSensor::UltrasonicSensor(PinName trigPin, PinName echoPin) : _trigPin(trigPin), _echoPin(echoPin) {
    _echoPin.rise([&] { this->echoStart(); });
    _echoPin.fall([&] { this->echoEnd(); });
};

// Trigger a pulse from the sensor.
void UltrasonicSensor::triggerSensor() {
    _trigPin = 0;
    wait_us(2);
    _trigPin = 1;
    wait_us(10);
    _trigPin = 0;
};

// Start a timer when we start to recieve back a pulse.
void UltrasonicSensor::echoStart() {
    _timer.reset();
    _timer.start();
}

// Stop the timer when the echo pulse ends.
void UltrasonicSensor::echoEnd() {
    _timer.stop();
    _duration = _timer.elapsed_time().count();
}

// Calculate the distance (in cm) that the wave travelled in one direction.
float UltrasonicSensor::readDistance() {
    triggerSensor();
    return _duration * 0.034 / 2;
};