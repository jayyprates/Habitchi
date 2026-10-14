#include "screens/main_screen.h"
#include "screens/base/screen_enum.h"
#include "screen_manager.h"

MainScreen::MainScreen() : Screen(ScreenId::Main, "Main", false) {}

void MainScreen::show() {
    handleDrawText(
        "No habit created yet.", 
        display.width() / 2, 
        display.height() / 2, 
        2, 
        false, 
        false, 
        TextAlignH::CENTER
    );
    handleDrawText(
        "Press 'OK' to start", 
        display.width() / 2, 
        display.height() / 2 + 25, 
        1, 
        false, 
        false, 
        TextAlignH::CENTER
    );
}

void MainScreen::onOkBtnPressed() {
    changeScreen(ScreenId::Menu);
}

void MainScreen::onDownBtnPressed() {
    // ...
}

void MainScreen::onUpBtnPressed() {
    // ...
}
