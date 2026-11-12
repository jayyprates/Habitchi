#include "screens/main_screen.h"
#include "screens/base/screen_enum.h"
#include "screen_manager.h"

#include "habit.h"
#include "habit_manager.h"
#include <RTClib.h>

#include "sprites/adult.h"
#include "display.h"

#define HORIZONTAL_INFORMATION_START 150
extern RTC_DS3231 rtc;
extern const uint8_t LED_PIN; // definido en main.cpp


MainScreen::MainScreen() : Screen(ScreenId::Main, "Main", false) {}

bool MainScreen::isHabitValid(const Habit& habit) {
    // Si la EEPROM está virgen (0xFF) o totalmente vacía
    if ((uint8_t)habit.name[0] == 0xFF || habit.name[0] == '\0') {
        return false;
    }

    // Recorre el nombre buscando al menos un carácter imprimible (ASCII > 32)
    for (size_t i = 0; i < sizeof(habit.name); i++) {
        if (habit.name[i] == '\0') break;
        if ((uint8_t)habit.name[i] > 32 && (uint8_t)habit.name[i] != 0xFF) {
            return true; // Encontró al menos una letra válida
        }
    }
    return false;
} 

void MainScreen::show() {
    // 1. Cargar explícitamente sobre el atributo miembro de la clase
    this->current_habit = loadHabit(0);

    // 3. Renderizado en pantalla
    if (!isHabitValid(this->current_habit)) {
        handleDrawText(
            "Nenhum habito criado", 
            display.width() / 2, 
            display.height() / 2 - 10, 
            1, 
            false, 
            false, 
            TextAlignH::CENTER
        );
        handleDrawText(
            "Pressione OK duas vezes", 
            display.width() / 2, 
            display.height() / 2 + 10, 
            1, 
            false, 
            false, 
            TextAlignH::CENTER
        );
    } else {
        // Draw sprite
        drawBitmapScaled(
            20, 40,
            adult_spriteadulto,
            ADULT_SPRITE_W,
            ADULT_SPRITE_H,
            2,
            GxEPD_BLACK
        );
        // Dibujar Nombre del hábito
        handleDrawText(
            "Habito:",
            HORIZONTAL_INFORMATION_START, 
            10, 
            1, 
            false, 
            false
        );
        handleDrawText(
            this->current_habit.name,
            HORIZONTAL_INFORMATION_START,
            30,
            2, 
            false, 
            false
        );

        // Dibujar Racha formateada
        char streak_buffer[16];
        snprintf(streak_buffer, sizeof(streak_buffer), "%u d", this->current_habit.counter);
        
        handleDrawText(
            "Streak:",
            HORIZONTAL_INFORMATION_START, 
            60, 
            1, 
            false, 
            false
        );
        handleDrawText(
            streak_buffer,
            HORIZONTAL_INFORMATION_START, 
            80, 
            2, 
            false, 
            false
        );


        // Marcou hoje?
        // Si canTrackHabit devuelve 'false', significa que pasaron menos de 24 horas -> ya trackeó
        DateTime now = rtc.now();
        uint32_t current_timestamp = now.unixtime();
        bool tracked_today = !canTrackHabit(this->current_habit, current_timestamp);

        handleDrawText(
            "Marcou hoje?:",
            HORIZONTAL_INFORMATION_START, 
            110, 
            1, 
            false
        );
        handleDrawText(
            tracked_today ? "Sim" : "Nao",
            HORIZONTAL_INFORMATION_START, 
            130, 
            2, 
            false
        );
    }
}

void MainScreen::onOkBtnPressed() {
    this->current_habit = loadHabit(0);

    if (!isHabitValid(this->current_habit)) {
        return;
    }

    DateTime now = rtc.now();
    uint32_t current_timestamp = now.unixtime();

    if (trackHabit(this->current_habit, current_timestamp, 0)) {
        Serial.println(F("[* MainScreen] - Trackeo exitoso, redibujando..."));
        beepSuccess();
        handleDraw();
    } else {
        Serial.println(F("[* MainScreen] - Bloqueado: aun no pasan 24h"));
        defaultFailBeep();
    }
}

void MainScreen::onDownBtnPressed() {
    onOkBtnPressed();
}

void MainScreen::onUpBtnPressed() {
    onOkBtnPressed();
}

void MainScreen::onDoubleOkBtnPressed() {
    changeScreen(ScreenId::Menu);
}

// 3 pitidos cada vez mas agudos, pausa y un pitido final
void MainScreen::beepSuccess() {
    pinMode(LED_PIN, OUTPUT);

    for (uint8_t i = 0; i < 3; i++) {
        beep(250 - i * 25, 50);
        delay(50);
    }

    delay(400);
    beep(125, 50);
}