#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include "display.h"
#include "screen_enum.h"
#include "alignment_enum.h"

class Screen {
public:
    explicit Screen(
        const ScreenId id,
        const String& title, 
        const boolean showTitle
    ) : id(id), title(title), showTitle(showTitle) {}
    virtual ~Screen() = default;
    
    void handleDraw(boolean full = false);
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

    void drawBitmapScaled(
        int16_t x,
        int16_t y,
        const unsigned char* bitmap,
        uint16_t w,
        uint16_t h,
        uint8_t scale,
        uint16_t color,
        boolean partial = false
    );

    void beep(uint16_t halfPeriodUs, uint16_t durationMs);
    void defaultFailBeep();
    void defaultSuccessBeep();
    
    virtual void show() = 0;

    virtual void onOkBtnPressed() {};
    virtual void onDoubleOkBtnPressed() {};
    virtual void onUpBtnPressed() {};
    virtual void onDoubleUpBtnPressed() {};
    virtual void onDownBtnPressed() {};
    
    const ScreenId id;

protected:
    const String title;
    const boolean showTitle;
};

#endif