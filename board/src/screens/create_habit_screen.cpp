#include "screens/create_habit_screen.h"
#include <screen_manager.h>

CreateHabitScreen::CreateHabitScreen() : Screen(ScreenId::Create, "Create Habit", false) {}

void CreateHabitScreen::show() {
    String text(characters);
    if (charsCounter < MAX_CHARACTERS) {
        text += currentChar;
    }

    //handleDrawText("Habito:", MENU_H_PADDING, 80, 1);
    handleDrawText(text, MENU_H_PADDING, 100, 2);

    for (int i = 0; i < 2; i++) {
        handleDrawText(
            buttons[i].title, 
            buttons[i].x, 
            buttons[i].y,
            2,
            false
        );
    };

    int x, y;
    switch(selectedButton) {
        case 0:
        case 1:
            x = buttons[selectedButton].x;
            y = buttons[selectedButton].y;
            break;
        case 2:
            x = MENU_H_PADDING;
            y = 100;
            break;
        default:
            // ???
            break;
    }

    if (!editing) {
        drawPointer(x, y, false);
    }

    if (editing) {
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds(text, MENU_H_PADDING, 100, &x1, &y1, &w, &h);
        display.fillTriangle(
            // X, Y
            x1 + w - 12,     85,
            (x1 + w - 8),     80,
            (x1 + w - 4),     85,
            GxEPD_BLACK
        );

        display.fillTriangle(
            // X, Y
            x1 + w - 12,     100 + h,
            (x1 + w - 8),     100 + h + 5,
            (x1 + w - 4),     100 + h,
            GxEPD_BLACK
        );
    }
}

void CreateHabitScreen::drawPointer(uint16_t x, uint16_t y, boolean partial) {
    display.fillTriangle(
        // X, Y
        x - 12 - 8,     y - 12 / 2,
        x - 8,                 y,
        x - 12 - 8,     y + 12 / 2,
        GxEPD_BLACK
    );
}

void CreateHabitScreen::onOkBtnPressed() {
    if (editing) {
        if (charsCounter >= MAX_CHARACTERS) return;

        characters[charsCounter++] = currentChar;
        characters[charsCounter] = '\0';
        currentChar = 'A';


    handleDraw();
    } else {
        if (selectedButton == 2) {
            editing = true;


    handleDraw();
        } else if (selectedButton == 1) {
            selectedButton = 0;
            memset(characters, 0, sizeof(characters));  
            charsCounter = 0;
            currentChar = 'A';
            changeScreen(ScreenId::Menu);
        } else if (selectedButton == 0) {
            selectedButton = 0;
            memset(characters, 0, sizeof(characters)); 
            charsCounter = 0;
            currentChar = 'A';
            changeScreen(ScreenId::Main);
        } 
    }
    
}

void CreateHabitScreen::onDoubleOkBtnPressed() {
    editing = false;

    if (!editing) {
        handleDraw();
    }
}

void CreateHabitScreen::onDoubleUpBtnPressed() {
    if (charsCounter == 0) return;
 
    currentChar = characters[--charsCounter];
    characters[charsCounter] = '\0';
 
    handleDraw();
}

void CreateHabitScreen::onDownBtnPressed() {
    if (!editing) {
        selectedButton += 1;

        if (selectedButton > 2) {
            selectedButton = 0;
        }
    } else {
        if (charsCounter >= MAX_CHARACTERS) return;

        currentChar = (currentChar == 'Z') ? 'A' : (char)(currentChar + 1);
    }

    handleDraw();
}

void CreateHabitScreen::onUpBtnPressed() {
    if (!editing) {
        selectedButton -= 1;

        if (selectedButton < 0) {
            selectedButton = 2;
        }
    } else {
        if (charsCounter >= MAX_CHARACTERS) return;

        currentChar = (currentChar == 'A') ? 'Z' : (char)(currentChar - 1);
    }

    handleDraw();
}