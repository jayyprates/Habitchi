#ifndef TEXT_ALIGN_H
#define TEXT_ALIGN_H

#include <Arduino.h>
enum class TextAlignH : uint8_t {
    LEFT,
    CENTER,
    RIGHT
};

enum class TextAlignV : uint8_t {
    TOP,
    CENTER,
    BOTTOM
};

#endif