#include "screen.h"
#include <string.h>
#include "alignment_enum.h"

/*
    @TODO
    There is a lot of room for improvement here
*/

extern const uint8_t LED_PIN; // definido en main.cpp

// Dibuja los pixeles del bitmap (1 bit por pixel, en PROGMEM) ampliados por 'scale'
static void drawBitmapPixels(
    int16_t x,
    int16_t y,
    const unsigned char* bitmap,
    uint16_t w,
    uint16_t h,
    uint8_t scale,
    uint16_t color
) {
    const uint16_t bytesPerRow = (w + 7) / 8;

    for (uint16_t row = 0; row < h; row++) {
        for (uint16_t col = 0; col < w; col++) {

            uint8_t byte = pgm_read_byte(
                bitmap + row * bytesPerRow + col / 8
            );

            if (byte & (0x80 >> (col % 8))) {
                display.fillRect(
                    x + col * scale,
                    y + row * scale,
                    scale,
                    scale,
                    color
                );
            }
        }
    }
}

void Screen::drawBitmapScaled(
    int16_t x,
    int16_t y,
    const unsigned char* bitmap,
    uint16_t w,
    uint16_t h,
    uint8_t scale,
    uint16_t color,
    bool partial
) {
    if (partial) {
        display.setPartialWindow(x, y, w * scale, h * scale);
        display.firstPage();

        do {
            display.fillScreen(GxEPD_WHITE);
            drawBitmapPixels(x, y, bitmap, w, h, scale, color);
        } while (display.nextPage());
    } else {
        drawBitmapPixels(x, y, bitmap, w, h, scale, color);
    }
}

void Screen::handleDrawText(
    const String& text,
    int16_t x,
    int16_t y,
    uint8_t textSize,
    bool partial,
    bool inverted,
    TextAlignH hAlignment,
    TextAlignV vAlignment
) {
    display.setTextColor(inverted ? GxEPD_WHITE : GxEPD_BLACK);
    display.setTextSize(textSize);

    int16_t ox, oy;
    uint16_t bw, bh;
    display.getTextBounds(text, 0, 0, &ox, &oy, &bw, &bh);

    switch (hAlignment) {
        case TextAlignH::CENTER:
            x -= bw / 2;
            break;
        case TextAlignH::RIGHT:
            x -= bw;
            break;
        default:
            break;
    }

    switch (vAlignment) {
        case TextAlignV::CENTER:
            y -= bh / 2;
            break;
        case TextAlignV::BOTTOM:
            y -= bh;
            break;
        default:   // TOP
            break;
    }

    int16_t bx = x + ox;
    int16_t by = y + oy;

    if (partial) {
        display.setPartialWindow(bx, by, bw, bh);
        display.firstPage();

        do {
            display.fillScreen(inverted ? GxEPD_BLACK : GxEPD_WHITE);
            display.setCursor(x, y);
            display.print(text);
        } while (display.nextPage());
    } else {
        if (inverted) {
            display.fillRect(bx, by, bw, bh, GxEPD_BLACK);
        }

        display.setCursor(x, y);
        display.print(text);
    }
}

void Screen::handleDraw(boolean full) {
   if (full) {
        display.setFullWindow();
    } else {
        display.setPartialWindow(0, 0, display.width(), display.height());
    }

    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);

        if (showTitle) {
            constexpr int16_t PADDING = 3;

            int16_t x1, y1;
            uint16_t w, h;
            display.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);

            display.fillRect(0, 0, w + 2 * PADDING, h + 2 * PADDING, GxEPD_BLACK);

            // texto blanco encima
            display.setTextColor(GxEPD_WHITE);
            display.setCursor(PADDING - x1, PADDING - y1);
            display.print(title);
        }

        display.setTextColor(GxEPD_BLACK);  // restaura el color para las hijas
        show();
    } while (display.nextPage());
}

// Onda cuadrada en el pin: suena el buzzer y el LED queda prendido
void Screen::beep(uint16_t halfPeriodUs, uint16_t durationMs) {
    const uint32_t start = millis();
    while (millis() - start < durationMs) {
        digitalWrite(LED_PIN, HIGH);
        delayMicroseconds(halfPeriodUs);
        digitalWrite(LED_PIN, LOW);
        delayMicroseconds(halfPeriodUs);
    }
}

void Screen::defaultFailBeep() {
    pinMode(LED_PIN, OUTPUT);
    beep(80, 500); // 80 -> ~6 kHz
}

void Screen::defaultSuccessBeep() {
    // Beep Beep! 
    pinMode(LED_PIN, OUTPUT);
    beep(100, 100); // 100 -> ~5 kHz
    delay(50);
    beep(100, 100);
}