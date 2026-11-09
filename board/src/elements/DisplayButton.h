#ifndef DISPLAY_BUTTON_H
#define DISPLAY_BUTTON_H

#include "Arduino.h"

enum class DisplayButtonId : uint8_t { 
    // CREATE HABIT
    CREATE_HABIT_OK, 
    CREATE_HABIT_CANCEL,

    // MENU
    MENU_CREATE, 
    MENU_EDIT, 
    MENU_SUSPENSE, 
    MENU_TURN_OFF, 
    MENU_BACK
};

struct DisplayButton {
    DisplayButtonId id;
    String title;
    boolean selected;
    uint16_t x;
    uint16_t y;
};

#endif