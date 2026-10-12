#include "screens/splash_screen.h"
#include "screen_enum.h"
#include "screens/base/logo_habitchi.h"

SplashScreen::SplashScreen() : Screen(ScreenId::Splash, "Splash", false) {}

void SplashScreen::show() {
    int logoX = display.width() / 2 - LOGO_W - 16;
    int logoY = (display.height() - LOGO_H) / 2;

    display.drawBitmap(logoX, logoY, logo_habitchi, LOGO_W, LOGO_H,
                       GxEPD_WHITE, GxEPD_BLACK);

    handleDrawText(
        "HABITCHI", 
        display.width() / 2, 
        display.height() / 2, 
        2, 
        false, 
        false, 
        TextAlignH::LEFT
    );
}
