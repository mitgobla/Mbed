// Example program using a DHT22 sensor, a buzzer, and the built-in RGB LED on the FRDM-K64F board.
// The LED colour changes depending on the range of temperature.
// The buzzer beeps when the program starts, and will beep at high temperatures.
// The temperature and humidity are printed so can be monitored over serial.
// Written By Ben Dodd

#include "mbed.h"
#include <array>

// Library from https://os.mbed.com/teams/Thing-Innovations/code/DHT/
// Modified to fix depreciated "wait_ms" usage. 
#include "DHT.h"

// My basic LED library
#include "LED.h"

// Constants
constexpr float BUZZER_FREQUENCY = 400.0f;
constexpr float BUZZER_DUTY_CYCLE = 0.75f;

// Sensors
// DHT data port is connected to D2 port
DHT sensor(ARDUINO_UNO_D2, DHT22);

// Buzzer is connected to D3 port
PwmOut buzzer(ARDUINO_UNO_D3);

// LED (Red, Green, Blue channels)  
std::array<DigitalOut, 3> leds = {DigitalOut(LED1), DigitalOut(LED2), DigitalOut(LED3)};
LED light(leds);

int status;
int temperature;
int humidity;

// Beeps the buzzer the specified number of times.
// If the amount specified is less than 1, then the buzzer will sound once.
void beep(int amount) {
    amount = std::min(amount, 1);
    for (int i = 0; i < amount; i++) {
        buzzer = BUZZER_DUTY_CYCLE;
        ThisThread::sleep_for(100ms);
        buzzer = 0.0f;
        ThisThread::sleep_for(100ms);
    }
}

int main()
{
    buzzer.period(1.0 / BUZZER_FREQUENCY);
    // Beep to indicate we are ready
    beep(1);
    while (true) {
        status = sensor.readData();
        if (status == ERROR_NONE) {
            temperature = sensor.ReadTemperature(CELCIUS);
            humidity = sensor.ReadHumidity();

            if (temperature < 5) {
                light.setColor(BLUE);
            } else if (temperature < 15) {
                light.setColor(CYAN);
            } else if (temperature < 25) {
                light.setColor(GREEN);
            } else if (temperature < 30) {
                beep(2);
                light.setColor(YELLOW);
            } else {
                beep(3);
                light.setColor(RED);
            }
            printf("Temperature (C): %d, Humidity: %d\n", temperature, humidity);
        }
        ThisThread::sleep_for(5s);
    }
}

