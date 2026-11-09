#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    explicit Button(
        uint8_t pin, 
        uint16_t debounceMs = 30
    ) : pin(pin), debounceMs(debounceMs) {}

    void begin() {
        pinMode(pin, INPUT_PULLUP);
        stable = digitalRead(pin);
        lastRead = digitalRead(pin);
    }

    // Lee el pin (con antirrebote) y, si hubo un click, lo deja guardado hasta que alguien
    // lo consuma con presseed(). Se puede llamar muy seguido, por ejemplo mientras el
    // display refresca, sin perder clicks.
    void update() {
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
                pressedLatch = true;
            }
        }
    }

    // true una sola vez por click
    bool presseed() {
        update();

        const bool wasPressed = pressedLatch;
        pressedLatch = false;
        return wasPressed;
    }

private:
    const uint8_t pin;
    const uint16_t debounceMs;
    bool stable = HIGH;
    bool lastRead = HIGH;
    bool pressedLatch = false;
    uint32_t lastChange = 0;
};

#endif