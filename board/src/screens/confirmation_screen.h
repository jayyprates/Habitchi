#ifndef CONFIRMATION_SCREEN_H
#define CONFIRMATION_SCREEN_H

#include <screens/base/screen.h>

class ConfirmationScreen : public Screen {
public:
    ConfirmationScreen();
    void show() override;
    void onOkBtnPressed() override;
    void onUpBtnPressed() override;
    void onDownBtnPressed() override;

private:
    boolean yesSelected = false;

    void drawOptions();
    void redrawOptions();
    void toggleSelection();
};

#endif
