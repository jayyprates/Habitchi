#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "screens/base/screen.h"
#include "habit.h"

class MainScreen : public Screen {
private:
    Habit current_habit;
    bool isHabitValid(const Habit& habit);
    void draw(bool partial = false);
public:
    MainScreen();
    void show() override;
    void onOkBtnPressed() override;
    void onDownBtnPressed() override;
    void onUpBtnPressed() override;
    void onDoubleOkBtnPressed() override;

    void beepSuccess();
};

#endif // MAIN_SCREEN_H