#ifndef CREATE_HABIT_H
#define CREATE_HABIT_H

#include "screens/base/screen.h"
#include "screens/base/screen_enum.h"

#include <Arduino.h>
#include <elements/DisplayButton.h>

#define MAX_CHARACTERS 24
#define START_WRITING_X 4
#define START_WRITING_Y 64

#define MENU_H_PADDING 30

class CreateHabitScreen : public Screen {
public:
    CreateHabitScreen();
    void show() override;
    void onOkBtnPressed() override;
    void onDoubleOkBtnPressed() override;
    void onDoubleUpBtnPressed() override;
    void onUpBtnPressed() override;
    void onDownBtnPressed() override;
    void drawPointer(uint16_t x, uint16_t y, boolean partial = false);


private:
    int selectedButton = 0;
    boolean editing = false;
    char currentChar = 'A';                     // letra que se esta eligiendo
    uint8_t charsCounter = 0;                   // letras ya confirmadas con OK
    char characters[MAX_CHARACTERS + 1] = {0};  // texto confirmado (termina en '\0')

    DisplayButton buttons[2] = {
        {DisplayButtonId::CREATE_HABIT_OK, "ACEITAR", false, MENU_H_PADDING, 10},
        {DisplayButtonId::CREATE_HABIT_CANCEL, "VOLTAR", false, MENU_H_PADDING, 40}
    };
};

#endif