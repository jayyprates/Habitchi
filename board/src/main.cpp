// @ Packages
#include <Arduino.h>

// @ Project
// * Modules
#include "display.h"
#include "button.h"
#include "screen_manager.h"


// * Screens
#include "screens/base/screen.h"
#include "screens/splash_screen.h"
#include "screens/main_screen.h"
#include "screens/base/screen_enum.h"
#include "screens/menu_screen.h"

#define MAX_CHANGES_BEFORE_FULL_REFRESH 10
#define SPLASH_DURATION_MS 2500

constexpr uint8_t OK_BUTTON_PIN = 2;
constexpr uint8_t UP_BUTTON_PIN = 3;
constexpr uint8_t DOWN_BUTTON_PIN = 4;

constexpr uint32_t SERIAL_BAUD = 115200;

SplashScreen splash;
MainScreen mainScreen;
MenuScreen menuScreen;

Screen* current = &splash;
bool splashDone = false;
uint32_t splashStart = 0;
ScreenId lastScreen = ScreenId::Menu;

Button okButton(OK_BUTTON_PIN);
Button upButton(UP_BUTTON_PIN);
Button downButton(DOWN_BUTTON_PIN);

uint8_t screenChangesCounter = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println(F("boot"));

    display.init(SERIAL_BAUD, true, 2, false);
    display.setRotation(1);

    okButton.begin();
    upButton.begin();
    downButton.begin();

    current->handleDraw();
    splashStart = millis();
}

void loop() {
    // Loading screen
    if (!splashDone && millis() - splashStart >= SPLASH_DURATION_MS) {
        current = &mainScreen;
        splashDone = true;
    }
    
    // Screen change
    if (lastScreen != current->id) {
        lastScreen = current->id;
        if (screenChangesCounter == MAX_CHANGES_BEFORE_FULL_REFRESH) {
          // After 10 screen changes we do a fullscreen clean to avoid ghosting
          current->handleDraw(true);
          screenChangesCounter = 0;
        } else {
          current->handleDraw();
        }
    }

    if (okButton.presseed()) {
      Serial.println(F("[* DEBUG] - OK BUTTON PRESSED"));
      current->onOkBtnPressed();
    }

    if (upButton.presseed()) {
      Serial.println(F("[* DEBUG] - UP BUTTON PRESSED"));
      current->onUpBtnPressed();
    }

    if (downButton.presseed()) {
      Serial.println(F("[* DEBUG] - DOWN BUTTON PRESSED"));
      current->onDownBtnPressed();
    }
}

void changeScreen(ScreenId newScreen) {
  Serial.println(F("[* DEBUG] - CHANGING SCREEN"));

  screenChangesCounter += 1;

  switch(newScreen) {
    case ScreenId::Main:
      current = &mainScreen;
      break;
    case ScreenId::Menu:
      current = &menuScreen;
      break;
    default:
      break;
  };
}