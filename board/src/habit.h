#ifndef HABIT_H
#define HABIT_H

#include <Arduino.h>
#include <RTClib.h>

struct Habit {
    char name[20];          // Nombre del hábito
    uint16_t counter;       // Contador de veces completadas
    uint32_t last_tracked;  // Timestamp Unix de la última vez que se trackeó
};

#endif