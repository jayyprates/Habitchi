
// @ Packages
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

// @ Project
// * Modules
#include "display.h"
#include "button.h"
#include "screen_manager.h"
#include "habit.h"
#include "habit_manager.h"

// * Screens
#include "screens/base/screen.h"
#include "screens/splash_screen.h"
#include "screens/main_screen.h"
#include "screens/create_habit_screen.h"
#include "screens/base/screen_enum.h"
#include "screens/menu_screen.h"

#define MAX_CHANGES_BEFORE_FULL_REFRESH 10
#define SPLASH_DURATION_MS 2500

#define DEBUG true

constexpr uint8_t OK_BUTTON_PIN = 2;
constexpr uint8_t UP_BUTTON_PIN = 3;
constexpr uint8_t DOWN_BUTTON_PIN = 4;

constexpr uint32_t SERIAL_BAUD = 115200;

constexpr uint16_t DOUBLE_PRESS_WINDOW_MS = 300;

enum class Press : uint8_t { None, Single, Double };

struct DoublePressDetector {
    bool pending = false;
    uint32_t since = 0;

    Press update(bool pressed) {
        if (pressed) {
            if (pending && millis() - since < DOUBLE_PRESS_WINDOW_MS) {
                pending = false;
                return Press::Double;
            }

            const bool hadExpired = pending;
            pending = true;
            since = millis();
            return hadExpired ? Press::Single : Press::None;
        }

        if (pending && millis() - since >= DOUBLE_PRESS_WINDOW_MS) {
            pending = false;
            return Press::Single;
        }

        return Press::None;
    }
};

SplashScreen splashScreen;
MainScreen mainScreen;
MenuScreen menuScreen;
CreateHabitScreen createScreen;

Screen* current = &splashScreen;
bool splashDone = false;
uint32_t splashStart = 0;
ScreenId lastScreen = ScreenId::Splash;

Button okButton(OK_BUTTON_PIN);
Button upButton(UP_BUTTON_PIN);
Button downButton(DOWN_BUTTON_PIN);

uint8_t screenChangesCounter = 0;

DoublePressDetector okDetector;
DoublePressDetector upDetector;

void pollButtonsWhileBusy(const void*) {
    okButton.update();
    upButton.update();
    downButton.update();
}

// -------- RTC (DS3231) --------
RTC_DS3231 rtc;
bool rtcOk = false;
constexpr uint16_t RTC_DEBUG_INTERVAL_MS = 5000;
uint32_t lastRtcDebug = 0;

void rtcInit() {
    Wire.begin();
    rtcOk = rtc.begin();

    if (!rtcOk) {
        Serial.println(F("[* DEBUG] - RTC NO ENCONTRADO (revisar SDA->A4, SCL->A5, VCC, GND)"));
        return;
    }

    if (rtc.lostPower()) {
        Serial.println(F("[* DEBUG] - RTC perdio la energia, ajustando con la hora de compilacion"));
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    Serial.println(F("[* DEBUG] - RTC OK"));
}

void rtcDebugPrint() {
    if (!rtcOk || millis() - lastRtcDebug < RTC_DEBUG_INTERVAL_MS) return;
    lastRtcDebug = millis();

    DateTime now = rtc.now();
    Serial.print(F("[* DEBUG] - RTC: "));
    Serial.print(now.timestamp());
    Serial.print(F(" | unix: "));
    Serial.println(now.unixtime());
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println(F("boot"));

    rtcInit();
    display.init(SERIAL_BAUD, true, 2, false);
    display.setRotation(1);

    okButton.begin();
    upButton.begin();
    downButton.begin();

    display.epd2.setBusyCallback(pollButtonsWhileBusy);

    current->handleDraw();
}

void loop() {
  if (DEBUG) {
    rtcDebugPrint();
  }

  if (!splashDone && millis() - splashStart >= SPLASH_DURATION_MS) {
    current = &mainScreen;
    splashDone = true;
  }

  // Screen change
  if (lastScreen != current->id) {
      lastScreen = current->id;
      if (screenChangesCounter == MAX_CHANGES_BEFORE_FULL_REFRESH) {
        current->handleDraw(true);
        screenChangesCounter = 0;
      } else {
        current->handleDraw();
      }
  }

  switch (okDetector.update(okButton.presseed())) {
    case Press::Single:
      Serial.println(F("[* DEBUG] - OK BUTTON PRESSED"));
      current->onOkBtnPressed();
      break;
    case Press::Double:
      Serial.println(F("[* DEBUG] - OK BUTTON DOUBLE PRESSED"));
      current->onDoubleOkBtnPressed();
      break;
    default:
      break;
  }

  switch (upDetector.update(upButton.presseed())) {
    case Press::Single:
      Serial.println(F("[* DEBUG] - UP BUTTON PRESSED"));
      current->onUpBtnPressed();
      break;
    case Press::Double:
      Serial.println(F("[* DEBUG] - UP BUTTON DOUBLE PRESSED"));
      current->onDoubleUpBtnPressed();
      break;
    default:
      break;
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
    case ScreenId::Create:
      current = &createScreen;
      break;
    default:
      break;
  };
}
