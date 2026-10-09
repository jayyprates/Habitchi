#ifndef SCREEN_ENUM_H
#define SCREEN_ENUM_H

#include <Arduino.h>

enum class ScreenId : uint8_t {
  Splash,
  Main,
  Menu,
  Settings,
  Create,
  Edit
};

#endif