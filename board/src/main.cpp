#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// CS, DC, RST, BUSY
GxEPD2_BW<GxEPD2_266_BN, GxEPD2_266_BN::HEIGHT / 8> display(
    GxEPD2_266_BN(/*CS=*/6, /*DC=*/7, /*RST=*/8, /*BUSY=*/9));

void setup() {
  display.init(115200, true, 2, false);
  display.setRotation(1);                 // landscape: 296 x 152
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawRect(2, 2, display.width() - 4, display.height() - 4, GxEPD_BLACK);
    display.setCursor(20, 60);
    display.print("Hello, e-paper!");
    display.setCursor(20, 90);
    display.print("Arduino Nano OK");
  } while (display.nextPage());

  display.hibernate();
}

void loop() {
}