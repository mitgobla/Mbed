// A basic example of using the touchscreen functionality of a TFT LCD display that has an ILI9341 controller.
// Written by Ben Dodd (mitgobla)

#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "Arial12x12.h"
#include "UTouch.h"
#include <cstdio>
#include <chrono>


// TFT LCD Display
PinName csPin(ARDUINO_UNO_D8);
PinName resetPin(ARDUINO_UNO_D9);
PinName dcPin(ARDUINO_UNO_D10);
PinName mosiPin(ARDUINO_UNO_D11);
PinName sckPin(ARDUINO_UNO_D13);
PinName misoPin(ARDUINO_UNO_D12);

SPI_TFT_ILI9341 display(mosiPin, misoPin, sckPin, csPin, resetPin, dcPin);

// Touchscreen
PinName tirqPin(ARDUINO_UNO_D0); // T_IRQ
PinName tcsPin(ARDUINO_UNO_D3); // T_CS
PinName tsckPin(ARDUINO_UNO_D4); // T_CLK
PinName tmosiPin(ARDUINO_UNO_D2); // T_DIN
PinName tmisoPin(ARDUINO_UNO_D1); // T_DO

UTouch touch(tsckPin, tcsPin, tmosiPin, tmisoPin, tirqPin);

// Built-in LED
DigitalOut red_led(LED_RED);
DigitalOut green_led(LED_GREEN);

// Clear Button
InterruptIn sw3(SW3);
volatile bool clearFlag = false;

void clearScreen() {
    clearFlag = true;
}

// Last coordinate
int last_x = -1, last_y = -1;
Timer lineTimer;

// Draw a line using circles between two points.
// This is used since the touchscreen sensitivity is not great, and therefore creates a dotting effect when dragging the stylus across the screen.
// Using this method gives us joined up lines.
void drawThickLineWithCircles(SPI_TFT_ILI9341 &the_display, int x0, int y0, int x1, int y1, int radius, unsigned short color) {
    // Calculate the distance between the two points
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Calculate the increment in x and y for each step
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x0;
    float y = y0;
    for(int v=0; v<steps; v++) {
        x += xInc;
        y += yInc;
        the_display.fillcircle(x, y, radius, color);
    }
}

int main()
{
    red_led = 1;
    green_led = 1;

    sw3.fall(&clearScreen);
    
    display.set_orientation(3);
    touch.InitTouch(LANDSCAPE);
    touch.SetPrecision(PREC_EXTREME);

    display.foreground(White);
    display.background(Black);
    display.cls();

    // Write some instructions at the top of the screen.
    display.set_font((unsigned char*) Arial12x12);
    display.locate(2, 2);
    display.printf("Draw on the screen!");
    display.locate(2, 15);
    display.printf("[SW3] Clear");
    ThisThread::sleep_for(50ms);

    lineTimer.start();
    while (true) {
        if (touch.DataAvailable()) {
            touch.Read();
            // Turn the green LED on to indicate we are currently drawing.
            green_led = 0;
            int x = touch.GetX();
            int y = touch.GetY();

            // This range check ensures we aren't drawing over the instruction text
            if (x >= 0 && y >= 31) {
                if (last_x >= 0 && last_y >= 31) {
                    drawThickLineWithCircles(display, last_x, last_y, x, y, 3, Red);
                }
                last_x = x;
                last_y = y;
                lineTimer.reset();
            }
        } else {
            green_led = 1;
            
            // If the stylus has not touched the screen for more than 50ms, then we reset the last x and y coordinate.
            // Otherwise, a line would be drawn between every point even after lifting off the stylus.
            if (std::chrono::duration_cast<std::chrono::milliseconds>(lineTimer.elapsed_time()).count() > 50) {
                last_x = -1;
                last_y = -1;
            }
        }

        // Clear only the drawing portion of the screen if the clear button has been pressed.
        // Red led is on while the screen is being cleared. It takes some time.
        if (clearFlag) {
            red_led = 0;
            display.fillrect(0, 31, display.width() - 1, display.height() - 1, Black);
            clearFlag = false;
            red_led = 1;
        }
        wait_us(1);
    }
}
