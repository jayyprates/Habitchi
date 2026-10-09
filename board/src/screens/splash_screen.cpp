#include "screens/splash_screen.h"
#include "screen_enum.h"

SplashScreen::SplashScreen() : Screen(ScreenId::Splash, "Splash", false) {}

void SplashScreen::show() {
    display.setCursor(10, 40);
    display.setTextSize(2);
    display.print("SPLASHSCREEN\nINICIANDO SISTEMA");
}

void SplashScreen::interact() {}