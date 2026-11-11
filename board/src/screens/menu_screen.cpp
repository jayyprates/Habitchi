#include <screens/menu_screen.h>
#include <screens/base/screen_enum.h>
#include <string.h>
#include "screen_manager.h"
#include <elements/DisplayButton.h>
#define PADDING_LEFT 16
#include "habit.h"
#include "habit_manager.h"

MenuScreen::MenuScreen() : Screen(ScreenId::Menu, "Menu", false) {
}

void MenuScreen::show() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (i == selectedButton) {
            drawPointer(buttons[i].x, buttons[i].y, false);
        }

        handleDrawText(
            buttons[i].title, 
            buttons[i].x, 
            buttons[i].y,
            2,
            false
        );
    };
}

void MenuScreen::drawPointer(uint16_t x, uint16_t y, boolean partial) {
    //display.setPartialWindow(x, y, POINTER_W, POINTER_H);
    if (!partial) {
        display.fillTriangle(
            // X, Y
            x - POINTER_W - POINTER_H_PADDING,     y - POINTER_H / 2,
            x - POINTER_H_PADDING,                 y,
            x - POINTER_W - POINTER_H_PADDING,     y + POINTER_H / 2,
            GxEPD_BLACK
        );

        return;
    }

    // Clean the entire left column where the arrow goes
    display.setPartialWindow(0, 0, MENU_H_PADDING - 5, display.height());
    display.firstPage();

    do {
        display.fillScreen(GxEPD_WHITE);

        display.fillTriangle(
            // X, Y
            x - POINTER_W - POINTER_H_PADDING,     y - POINTER_H / 2,
            x - POINTER_H_PADDING,                 y,
            x - POINTER_W - POINTER_H_PADDING,     y + POINTER_H / 2,
            GxEPD_BLACK
        );
    } while (display.nextPage());
}

void MenuScreen::onOkBtnPressed() {
    switch(buttons[selectedButton].id) {
        case DisplayButtonId::MENU_CREATE:
            changeScreen(ScreenId::Create);
            break;
        case DisplayButtonId::MENU_DELETE:
            deleteHabit(0);
            changeScreen(ScreenId::Main);
            break;
        case DisplayButtonId::MENU_SUSPENSE:
            // TODO
            break;
        case DisplayButtonId::MENU_TURN_OFF:
            // TODO: Currently, only clearScreen() is called, but it should also call something like handleTurnOff() in main.cpp to turn the device off completely.
            display.clearScreen();
            break;
        case DisplayButtonId::MENU_BACK:
            changeScreen(ScreenId::Main);
            break;
        default:
        break;
    }

    selectedButton = 0;
}

void MenuScreen::onDownBtnPressed() {
    selectedButton += 1;

    if (selectedButton >= NUM_BUTTONS) {
        selectedButton = 0;
    }

    drawPointer(buttons[selectedButton].x, buttons[selectedButton].y, true);
}

void MenuScreen::onUpBtnPressed() {
    selectedButton -= 1;

    if (selectedButton < 0) {
        selectedButton = NUM_BUTTONS - 1;
    }

    drawPointer(buttons[selectedButton].x, buttons[selectedButton].y, true);
}
