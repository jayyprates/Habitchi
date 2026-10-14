#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#define POINTER_H 12
#define POINTER_W 12
#define POINTER_H_PADDING 8 
#define MENU_H_PADDING 30

#include <screens/base/screen.h>

constexpr uint8_t NUM_BUTTONS = 5;

enum class MenuButtonId : uint8_t { CREATE, EDIT, SUSPENSE, TURN_OFF, BACK };

struct MenuButton {
    MenuButtonId id;
    String title;
    boolean selected;
    uint16_t x;
    uint16_t y;
};

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

    MenuButton buttons[NUM_BUTTONS] = {
        {MenuButtonId::CREATE, "Criar habito", false, MENU_H_PADDING, 10},
        {MenuButtonId::EDIT, "Editar habito", false, MENU_H_PADDING, 40},
        {MenuButtonId::SUSPENSE, "Suspender", false, MENU_H_PADDING, 70},
        {MenuButtonId::TURN_OFF, "Apagar", false, MENU_H_PADDING, 100},
        {MenuButtonId::BACK, "Voltar", false, MENU_H_PADDING, 140},
    };
};
#endif