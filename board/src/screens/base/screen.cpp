#include "screen.h"

void Screen::clear() {
    display.setFullWindow();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
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