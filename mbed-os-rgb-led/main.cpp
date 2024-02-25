#include "mbed.h"
#include <chrono>
#include <cstdlib>
#include <ctime>

// RGB LED
PwmOut RED(ARDUINO_UNO_D5);
PwmOut GREEN(ARDUINO_UNO_D6);
PwmOut BLUE(ARDUINO_UNO_D7);

std::chrono::milliseconds getRandomSleep(int minSleep, int maxSleep) {
    int random_time = minSleep + std::rand() % (maxSleep - minSleep + 1);
    std::chrono::milliseconds duration(random_time);
    return duration;
};

void fade(PwmOut& led) {
    while (true) {
        for (float i = 0.0f; i <= 1.0f; i += 0.01f) {
            led = i;
            ThisThread::sleep_for(getRandomSleep(10,50));
        }
        getRandomSleep(0, 500);
        // Fade out
        for (float i = 1.0f; i >= 0.0f; i -= 0.01f) {
            led = i;
            ThisThread::sleep_for(getRandomSleep(10,50));
        }
        getRandomSleep(0, 500);
    }
}

// main() runs in its own thread in the OS
int main()
{

    RED.period_ms(1);
    GREEN.period_ms(1);
    BLUE.period_ms(1);

    std::srand(std::time(0));
    Thread thread_red;
    Thread thread_green;
    Thread thread_blue;

    thread_red.start([&] { fade(RED); });
    ThisThread::sleep_for(getRandomSleep(500, 1500));
    thread_green.start([&] { fade(GREEN); });
    ThisThread::sleep_for(getRandomSleep(500, 1500));
    thread_blue.start([&] { fade(BLUE); });

    while (true) {
        ThisThread::sleep_for(100ms);
    }
}

