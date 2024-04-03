// Library for a Capacitive Soil Moisture Sensor
// Written by Ben Dodd (mitgobla)

#ifndef MBED_MOISTURE_H
#define MBED_MOISTURE_H

#include "mbed.h"

class SoilMoistureSensor {
public:
    SoilMoistureSensor(PinName pin);

    float getReading();
    void saveDryReading();
    void saveWetReading();

    float getDryReading();
    float getWetReading();

    void setup();

private:
    AnalogIn _pin;
    int _id;
    char _filepath[25];
    float _minReading;
    float _maxReading;
    
    void readCalibration();
    void saveCalibration();
    float mapAndClamp(float value);
    
    static int _nextId;
    static const char* _path;

};

#endif