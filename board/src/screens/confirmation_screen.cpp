#include <screens/confirmation_screen.h>
#include <screens/base/screen_enum.h>
#include "screen_manager.h"
#include "pet.h"

constexpr int16_t CONFIRM_POINTER_W = 12;
constexpr int16_t CONFIRM_POINTER_H = 12;
constexpr int16_t CONFIRM_POINTER_PADDING = 8;

constexpr int16_t QUESTION_LINE_1_Y = 34;
constexpr int16_t QUESTION_LINE_2_Y = 58;
constexpr int16_t OPTIONS_Y = 112;
constexpr int16_t OPTIONS_AREA_H = 32;
constexpr int16_t YES_CENTER_X = 96;
constexpr int16_t NO_CENTER_X = 200;
constexpr int16_t OPTION_HALF_W = 18;

ConfirmationScreen::ConfirmationScreen() : Screen(ScreenId::Confirmation, "Confirmar", false) {
}

void ConfirmationScreen::show() {
    handleDrawText(F("Tem certeza que deseja"), display.width() / 2, QUESTION_LINE_1_Y, 2, false, false, TextAlignH::CENTER);
    handleDrawText(F("desistir do bichinho?"), display.width() / 2, QUESTION_LINE_2_Y, 2, false, false, TextAlignH::CENTER);

    display.drawFastHLine(40, 82, display.width() - 80, GxEPD_BLACK);

    drawOptions();
}

void ConfirmationScreen::drawOptions() {
    handleDrawText(F("SIM"), YES_CENTER_X, OPTIONS_Y, 2, false, false, TextAlignH::CENTER);
    handleDrawText(F("NAO"), NO_CENTER_X, OPTIONS_Y, 2, false, false, TextAlignH::CENTER);

    int16_t textLeft = (yesSelected ? YES_CENTER_X : NO_CENTER_X) - OPTION_HALF_W;

    display.fillTriangle(
        textLeft - CONFIRM_POINTER_W - CONFIRM_POINTER_PADDING,     OPTIONS_Y - CONFIRM_POINTER_H / 2,
        textLeft - CONFIRM_POINTER_PADDING,                         OPTIONS_Y,
        textLeft - CONFIRM_POINTER_W - CONFIRM_POINTER_PADDING,     OPTIONS_Y + CONFIRM_POINTER_H / 2,
        GxEPD_BLACK
    );
}

// só redesenha a parte das opções
void ConfirmationScreen::redrawOptions() {
    display.setPartialWindow(0, OPTIONS_Y - OPTIONS_AREA_H / 2, display.width(), OPTIONS_AREA_H);
    display.firstPage();

    do {
        display.fillScreen(GxEPD_WHITE);
        drawOptions();
    } while (display.nextPage());
}

void ConfirmationScreen::toggleSelection() {
    yesSelected = !yesSelected;
    redrawOptions();
}

void ConfirmationScreen::onOkBtnPressed() {
    boolean confirmed = yesSelected;

    yesSelected = false;

    if (confirmed) {
        giveUpPet();
        changeScreen(ScreenId::DeadPet);
    } else {
        changeScreen(ScreenId::Menu);
    }
}

void ConfirmationScreen::onUpBtnPressed() {
    toggleSelection();
}

void ConfirmationScreen::onDownBtnPressed() {
    toggleSelection();
}
