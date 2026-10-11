#include "screens/splash_screen.h"
#include "screen_enum.h"

SplashScreen::SplashScreen() : Screen(ScreenId::Splash, "Splash", false) {}

void SplashScreen::show() {
    handleDrawText(
        "Loading...", 
        display.width() / 2, 
        display.height() / 2, 
        2, 
        false, 
        false, 
        TextAlignH::CENTER
    );
}
