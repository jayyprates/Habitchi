#ifndef DEAD_PET_SCREEN_H
#define DEAD_PET_SCREEN_H

#include <screens/base/screen.h>

class DeadPetScreen : public Screen {
public:
    DeadPetScreen();
    void show() override;
    void onOkBtnPressed() override;

private:
    void drawTombstone();
};

#endif
