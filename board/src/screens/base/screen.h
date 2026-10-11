#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include "display.h"
#include "screens/screen_enum.h"
#include "alignment_enum.h"

class Screen {
public:
    explicit Screen(
        const ScreenId id,
        const String& title, 
        const boolean showTitle
    ) : id(id), title(title), showTitle(showTitle) {}
    virtual ~Screen() = default;
    
    void handleDraw();
    void handleDrawText(
        const String& text, 
        int16_t x, 
        int16_t y, 
        uint8_t textSize = 1,
        boolean partial = false,
        boolean inverted = false,
        TextAlignH hAlignment = TextAlignH::LEFT,
        TextAlignV vAlignment = TextAlignV::CENTER
    );

    virtual void show() = 0;
    virtual void clear();

    virtual void onOkBtnPressed() {};
    virtual void onUpBtnPressed() {};
    virtual void onDownBtnPressed() {};

    const ScreenId id;

protected:
    const String title;
    const boolean showTitle;
};

#endif