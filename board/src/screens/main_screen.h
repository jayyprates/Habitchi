#pragma once
#include "screens/base/screen.h"

class MainScreen : public Screen {
public:
    MainScreen();
    void show() override;
    void onOkBtnPressed() override;
    void onUpBtnPressed() override;
    void onDownBtnPressed() override;
};