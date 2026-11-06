#include <screens/dead_pet_screen.h>
#include <screens/base/screen_enum.h>
#include "screen_manager.h"
#include "pet.h"

constexpr int16_t TOMB_X = 30;
constexpr int16_t TOMB_Y = 28;
constexpr int16_t TOMB_W = 72;
constexpr int16_t TOMB_RADIUS = 22;
constexpr int16_t TOMB_BORDER = 3;
constexpr int16_t GROUND_Y = 120;
constexpr int16_t GROUND_H = 3;

constexpr int16_t TEXT_CENTER_X = 200;

DeadPetScreen::DeadPetScreen() : Screen(ScreenId::DeadPet, "Morto", false) {
}

void DeadPetScreen::drawTombstone() {
    int16_t h = GROUND_Y - TOMB_Y + TOMB_RADIUS;

    display.fillRoundRect(TOMB_X, TOMB_Y, TOMB_W, h, TOMB_RADIUS, GxEPD_BLACK);
    display.fillRoundRect(
        TOMB_X + TOMB_BORDER,
        TOMB_Y + TOMB_BORDER,
        TOMB_W - 2 * TOMB_BORDER,
        h - 2 * TOMB_BORDER,
        TOMB_RADIUS - TOMB_BORDER,
        GxEPD_WHITE
    );
    display.fillRect(TOMB_X - 1, GROUND_Y, TOMB_W + 2, h, GxEPD_WHITE);

    // chão
    display.fillRect(TOMB_X - 16, GROUND_Y, TOMB_W + 32, GROUND_H, GxEPD_BLACK);

    // cruz
    int16_t cx = TOMB_X + TOMB_W / 2;
    display.fillRect(cx - 1, TOMB_Y + 14, 3, 16, GxEPD_BLACK);
    display.fillRect(cx - 6, TOMB_Y + 19, 13, 3, GxEPD_BLACK);

    handleDrawText(F("RIP"), cx, TOMB_Y + 52, 2, false, false, TextAlignH::CENTER);
}

void DeadPetScreen::show() {
    drawTombstone();

    handleDrawText(F("Seu bichinho"), TEXT_CENTER_X, 52, 2, false, false, TextAlignH::CENTER);
    handleDrawText(F("morreu..."), TEXT_CENTER_X, 76, 2, false, false, TextAlignH::CENTER);
    handleDrawText(F("Pressione OK"), TEXT_CENTER_X, 108, 1, false, false, TextAlignH::CENTER);
    handleDrawText(F("para recomecar"), TEXT_CENTER_X, 120, 1, false, false, TextAlignH::CENTER);
}

void DeadPetScreen::onOkBtnPressed() {
    clearPet();
    changeScreen(ScreenId::Main);
}
