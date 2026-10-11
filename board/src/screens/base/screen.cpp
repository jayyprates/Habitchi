#include "screen.h"
#include <string.h>
#include "alignment_enum.h"

void Screen::clear() {
    display.setFullWindow();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
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

void Screen::handleDraw() {
    display.setFullWindow();
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