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
#include "screens/create_habit_screen.h"
#include "screens/base/screen_enum.h"
#include "screens/menu_screen.h"

#define MAX_CHANGES_BEFORE_FULL_REFRESH 10
#define SPLASH_DURATION_MS 2500

constexpr uint8_t OK_BUTTON_PIN = 2;
constexpr uint8_t UP_BUTTON_PIN = 3;
constexpr uint8_t DOWN_BUTTON_PIN = 4;

constexpr uint32_t SERIAL_BAUD = 115200;

// Ventana para detectar doble click. Un click simple se entrega recien cuando
// pasa esta ventana sin un segundo click.
constexpr uint16_t DOUBLE_PRESS_WINDOW_MS = 300;

enum class Press : uint8_t { None, Single, Double };

struct DoublePressDetector {
    bool pending = false;   // hubo un click esperando ver si viene un segundo
    uint32_t since = 0;

    // Llamar una vez por vuelta del loop, con el resultado de button.presseed()
    Press update(bool pressed) {
        if (pressed) {
            if (pending && millis() - since < DOUBLE_PRESS_WINDOW_MS) {
                pending = false;
                return Press::Double;
            }

            // Si quedaba un click viejo con la ventana vencida, se entrega ahora como
            // simple y este click pasa a ser el pendiente
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

SplashScreen splash;
MainScreen mainScreen;
MenuScreen menuScreen;
CreateHabitScreen createScreen;

Screen* current = &createScreen;
bool splashDone = false;
uint32_t splashStart = 0;
ScreenId lastScreen = ScreenId::Create;

Button okButton(OK_BUTTON_PIN);
Button upButton(UP_BUTTON_PIN);
Button downButton(DOWN_BUTTON_PIN);

uint8_t screenChangesCounter = 0;

DoublePressDetector okDetector;
DoublePressDetector upDetector;

// El e-paper tarda ~0.8 s en refrescar y el loop queda bloqueado esperando. GxEPD2 llama a
// esta funcion una y otra vez durante esa espera, asi los botones se siguen leyendo y el
// click queda guardado (Button::update) en vez de perderse.
void pollButtonsWhileBusy(const void*) {
    okButton.update();
    upButton.update();
    downButton.update();
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println(F("boot"));

    display.init(SERIAL_BAUD, true, 2, false);
    display.setRotation(1);

    okButton.begin();
    upButton.begin();
    downButton.begin();

    display.epd2.setBusyCallback(pollButtonsWhileBusy);

    current->handleDraw();
    //splashStart = millis();
}

void loop() {
    // Loading screen
    /*
    if (!splashDone && millis() - splashStart >= SPLASH_DURATION_MS) {
        current = &mainScreen;
        splashDone = true;
    }*/
    
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