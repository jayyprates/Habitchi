#include "screens/main_screen.h"
#include "screen_enum.h"

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
        "(^_^)", 
        display.width() / 2, 
        display.height() / 2 + 25, 
        2, 
        false, 
        false, 
        TextAlignH::CENTER
    );
}

void MainScreen::onOkBtnPressed() {
    // ...
}

void MainScreen::onDownBtnPressed() {
    // ...
}

void MainScreen::onUpBtnPressed() {
    // ...
}
