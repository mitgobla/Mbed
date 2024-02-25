#include "mbed.h"
#include "ultrasonic.h"
#include <cstdio>

// Clamp the input distances between min and max, since readings from an ultrasonic sensor
// have a limited range that is mostly accurate.
constexpr float MIN_DISTANCE = 10.0;
constexpr float MAX_DISTANCE = 50.0;

// Ultrasonic sensor
PinName trig(ARDUINO_UNO_D8);
PinName echo(ARDUINO_UNO_D9);

UltrasonicSensor sensor(trig, echo);

// RGB LED
PwmOut RED(ARDUINO_UNO_D5);
PwmOut GREEN(ARDUINO_UNO_D6);

int main()
{
    // Turn Red and Green LED off.
    RED.period_ms(1);
    GREEN.period_ms(1);
    RED = 0;
    GREEN = 0;

    while (true) {
            // Read distance from sensor
            float distance_in = sensor.readDistance();
            // Clamp distances between min and max constants.
            if (distance_in < MIN_DISTANCE) {
                RED = 1.0;
                GREEN = 0.0;
            } else if (distance_in > MAX_DISTANCE) {
                RED = 0.0;
                GREEN = 1.0;
            } else {
                // Interpolate the brightness of red/green depending on distance between max and min
                float factor = (distance_in - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE);
                RED = 1.0 - factor;
                GREEN = factor;
            }
            ThisThread::sleep_for(50ms);
    }
}

