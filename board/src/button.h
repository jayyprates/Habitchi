#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    explicit Button(uint8_t pin, uint16_t debounceMs = 30) : pin(pin), debounceMs(debounceMs) {}

    void begin() {
        pinMode(pin, INPUT_PULLUP);
        stable = digitalRead(pin);
        lastRead = digitalRead(pin);
    }

    bool presseed() {
        bool currentRead = digitalRead(pin);

        // There was a change
        if (currentRead != lastRead) {
            lastChange = millis();
            lastRead = currentRead;
        }


        // It passed more than 30ms since last change, to avoid blinky behavior
        if (millis() - lastChange >= debounceMs && currentRead != stable) {
            stable = currentRead;

            // Pressed
            if (stable == LOW) {
                return true;
            }
        }

        return false;
    }

private:
    const uint8_t pin;
    const uint16_t debounceMs;
    bool stable = HIGH;
    bool lastRead = HIGH;
    uint32_t lastChange = 0;
};

#endif