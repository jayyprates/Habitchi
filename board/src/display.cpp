#include "display.h"

Display display(Panel(DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_BUSY_PIN));

void drawBitmapScaled(
    int16_t x,
    int16_t y,
    const unsigned char* bitmap,
    uint16_t w,
    uint16_t h,
    uint8_t scale,
    uint16_t color
) {
    uint16_t bytesPerRow = (w + 7) / 8;

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