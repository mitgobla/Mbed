// Library for a Capacitive Soil Moisture Sensor
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "soilmoisturesensor.h"
#include <cstdio>

int SoilMoistureSensor::_nextId = 0;
const char* SoilMoistureSensor::_path = "/fs/";

SoilMoistureSensor::SoilMoistureSensor(PinName pin) : _id(_nextId++), _pin(pin) {}

/*
Setup the moisture sensor by defining its filename for storing calibrated values, and loading them.
This method must be ran before the main loop of the program.
*/
void SoilMoistureSensor::setup() {
    sprintf(_filepath, "%ssensor_%d.bin", _path, _id);
    readCalibration();
    printf("Sensor %d: Max %f, Min %f\n", _id, _minReading, _maxReading);
}

/*
Load the calibrated wet and dry values from the file.
If the file is not found or cannot be read, default values are used:
Wet: 0.0, Dry: 1.0
*/
void SoilMoistureSensor::readCalibration() {
    FILE *file = fopen(_filepath, "rb");
    if (file != NULL) {
        if(fread(&_minReading, sizeof(_minReading), 1, file) < 1 ||
        fread(&_maxReading, sizeof(_maxReading), 1, file) < 1 ) {
            _minReading = 0.0;
            _maxReading = 1.0;
        }
        fclose(file);
    }
}

/*
Save the calibrated wet and dry values to the file.
*/
void SoilMoistureSensor::saveCalibration() {
    FILE *file = fopen(_filepath, "wb");
    if (file != NULL) {
        fwrite(&_minReading, sizeof(_minReading), 1, file);
        fwrite(&_maxReading, sizeof(_maxReading), 1, file);
        fclose(file);
    }
}

/*
Clamp the passed value to between the calibrated wet and dry values of the sensor.
Then, map the value between 0.0 (dry) and 1.0 (wet).
*/
float SoilMoistureSensor::mapAndClamp(float value) {
    if (value > _maxReading) {
        value = _maxReading;
    } else if (value < _minReading) {
        value = _minReading;
    }

    float mappedValue = 1.0f - (value - _minReading) / (_maxReading - _minReading);
    return mappedValue;
}

/*
Record the dry reading of the sensor and save it.
*/
void SoilMoistureSensor::saveDryReading() {
    _maxReading = _pin.read();
    saveCalibration();
}

/*
Record the wet reading of the sensor and save it.
*/
void SoilMoistureSensor::saveWetReading() {
    _minReading = _pin.read();
    saveCalibration();
}

/*
Returns the calibrated dry reading of this sensor.
*/
float SoilMoistureSensor::getDryReading() {
    return _maxReading;
}

/*
Returns the calibrated wet reading of this sensor.
*/
float SoilMoistureSensor::getWetReading() {
    return _minReading;
}

/*
Return the reading from the moisture sensor, mapped between a value of 0.0 to 1.0.
Where 0.0 is considered the "dry" calibration of the sensor, and 1.0 is considered the "wet" calibration of the sensor.
*/
float SoilMoistureSensor::getReading() {
    return mapAndClamp(_pin.read());
}
