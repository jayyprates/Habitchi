#include "screens/main_screen.h"
#include "screen_enum.h"

MainScreen::MainScreen() : Screen(ScreenId::Main, "Main", true) {}

void MainScreen::show() {
    display.setCursor(10, 40);
    display.setTextSize(2);
    display.print("TELA DE INICIO");
}

void MainScreen::interact() {}

void MainScreen::onOkBtnPressed() {
   // ...
}

void MainScreen::onDownBtnPressed() {
    // ...
}

void MainScreen::onUpBtnPressed() {
    // ...
}
