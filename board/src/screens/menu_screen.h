#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#define POINTER_H 12
#define POINTER_W 12
#define POINTER_H_PADDING 8 
#define MENU_H_PADDING 30

#include <screens/base/screen.h>
#include <elements/DisplayButton.h>

constexpr uint8_t NUM_BUTTONS = 5;

class MenuScreen : public Screen {
public:
    MenuScreen();
    void show();
    void onOkBtnPressed() override;
    void onUpBtnPressed() override;
    void onDownBtnPressed() override;
    void drawPointer(uint16_t x, uint16_t y, boolean partial = false);
    void redrawSelection(uint8_t oldIdx, uint8_t newIdx);

private:
    int selectedButton = 0;

    DisplayButton buttons[NUM_BUTTONS] = {
        {DisplayButtonId::MENU_CREATE, "Criar habito", false, MENU_H_PADDING, 10},
        {DisplayButtonId::MENU_EDIT, "Editar habito", false, MENU_H_PADDING, 40},
        {DisplayButtonId::MENU_SUSPENSE, "Suspender", false, MENU_H_PADDING, 70},
        {DisplayButtonId::MENU_TURN_OFF, "Apagar", false, MENU_H_PADDING, 100},
        {DisplayButtonId::MENU_BACK, "Voltar", false, MENU_H_PADDING, 140},
    };
};
#endif