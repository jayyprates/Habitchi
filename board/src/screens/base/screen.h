#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include "display.h"
#include "screens/screen_enum.h"

class Screen {
public:
    explicit Screen(
        const ScreenId id,
        const String& title, 
        const boolean showTitle
    ) : id(id), title(title), showTitle(showTitle) {}
    virtual ~Screen() = default;
    
    void handleDraw();

    virtual void show() = 0;
    virtual void interact() = 0;
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