#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include <cstdio>
#include <array>
#include "LED.h"
#include "SPI_TFT_ILI9341.h"
#include "soilmoisturesensor.h"
#include "ProgressBar.h"

// Setup the display

PinName csPin(ARDUINO_UNO_D8);
PinName resetPin(ARDUINO_UNO_D9);
PinName dcPin(ARDUINO_UNO_D10);
PinName mosiPin(ARDUINO_UNO_D11);
PinName sckPin(ARDUINO_UNO_D13);
PinName misoPin(ARDUINO_UNO_D12);

SPI_TFT_ILI9341 display(mosiPin, misoPin, sckPin, csPin, resetPin, dcPin);

// Setup an array of moisture sensors
std::array<SoilMoistureSensor, 3> sensors = {
    SoilMoistureSensor(ARDUINO_UNO_A0),
    SoilMoistureSensor(ARDUINO_UNO_A1),
    SoilMoistureSensor(ARDUINO_UNO_A2)
};

// Setup an array of progress bars, that will be linked to the moisture sensors.
std::array<ProgressBar, sensors.size()> bars = {
    ProgressBar(display, 5, 5, display.height() - 5, 16),
    ProgressBar(display, 5, 21, display.height() - 5, 32),
    ProgressBar(display, 5, 37, display.height() - 5, 48)
};

// LED is used to indicate calibration state.
std::array<DigitalOut, 3> leds = {
    DigitalOut(LED1),
    DigitalOut(LED2),
    DigitalOut(LED3)
};
LED light(leds);

// Define the SD card and file system.
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);
FATFileSystem fs("fs");

// Button is used for running calibration process.
InterruptIn button(SW2);
volatile bool buttonPressed = false;

// Current state of the program
enum State {START_SEQUENCE, SAVE_MAX, SAVE_MIN_AND_END};
State currentState = START_SEQUENCE;

void setButtonPressed() {
    buttonPressed = true;
}

// main() runs in its own thread in the OS
int main()
{
    // Setup display
    display.set_orientation(1);
    display.foreground(White);
    display.background(Black);
    display.cls();

    button.fall(&setButtonPressed);
    fs.mount(&sd);
    light.setColor(OFF);
    // For every progress bar and moisture sensor, run their setup method.
    for (size_t i = 0; i < sensors.size(); ++i) {
        bars[i].setup();
        sensors[i].setup();
    }
    
    while (true) {
        // Pressing the button moves the state to the next one.
        // START_SEQUENCE means we will begin calibrating the sensors.
        // SAVE_MAX means the current reading of the sensors are saved to their dry reading
        // SAVE_MIN_AND_END means the current reading of the sensors are saved to their wet reading, and then we end the calibration sequence.
        if (buttonPressed) {
            switch (currentState) {
                case START_SEQUENCE:
                    currentState = SAVE_MAX;
                    light.setColor(RED);
                    break;
                case SAVE_MAX:
                    currentState = SAVE_MIN_AND_END;
                    for (SoilMoistureSensor& sensor : sensors) {
                        sensor.saveDryReading();
                    }
                    light.setColor(BLUE);
                    break;
                case SAVE_MIN_AND_END:
                    currentState = START_SEQUENCE;
                    for (SoilMoistureSensor& sensor : sensors) {
                        sensor.saveWetReading();
                    }
                    light.setColor(GREEN);
                    ThisThread::sleep_for(1000ms);
                    light.setColor(OFF);
                    break;
            }
            buttonPressed = false;
        }

        // Only check sensors for readings when we aren't in the calibration process.
        if (currentState == START_SEQUENCE) {
            for (size_t i = 0; i < sensors.size(); ++i) {
                float currentReading = sensors[i].getReading();
                // Update the progress bar color depending on the moisture.
                if (currentReading < 0.25) {
                    bars[i].setForegroundColor(Red);
                } else if (currentReading < 0.75) {
                    bars[i].setForegroundColor(Green);
                } else {
                    bars[i].setForegroundColor(Blue);
                }
                bars[i].setProgressPercentage(currentReading);
            }
        }
        ThisThread::sleep_for(500ms);
    }
    fs.unmount();
}

