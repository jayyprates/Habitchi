#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <GxEPD2_BW.h>

// Pins
constexpr uint8_t DISPLAY_CS_PIN   = 6;
constexpr uint8_t DISPLAY_DC_PIN   = 7;
constexpr uint8_t DISPLAY_RST_PIN  = 8;
constexpr uint8_t DISPLAY_BUSY_PIN = 9;

// Propiedades
constexpr uint16_t PAGE_SIZE = 19;

using Panel   = GxEPD2_266_BN;
using Display = GxEPD2_BW<Panel, PAGE_SIZE>;

extern Display display;  // la definición vive en display.cpp

#endif