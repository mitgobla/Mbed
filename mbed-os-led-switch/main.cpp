#include "mbed.h"
#include <string>

// LEDs
DigitalOut leds[3] = {DigitalOut(LED1), DigitalOut(LED2), DigitalOut(LED3)};
int states[8] = {0b000, 0b001, 0b010, 0b100, 0b011, 0b110, 0b101, 0b111};
std::string colors[8] = {"Off", "Red", "Green", "Blue", "Yellow", "Cyan", "Purple", "White"};
int state = 0;
volatile bool update_flag = false;

// Buttons
InterruptIn sw3(SW3);
InterruptIn sw2(SW2);

void update_leds() {
    for (int i = 0; i < 3; i++) {
        leds[i] = (states[state] & (1 << i)) ? 0 : 1;
    }
    update_flag = true;
}

void sw3_down() {
    state = (state + 1) % 8;
    update_leds();
}

void sw2_down() {
    state = (state + 7) % 8;
    update_leds();
}

int main() {
    update_leds();
    sw3.fall(&sw3_down);
    sw2.fall(&sw2_down);

    while (true) {
        if (update_flag) {
            printf("Color: %s\n", colors[state].c_str());
            update_flag = false;
        }
        ThisThread::sleep_for(100ms);
    }
}