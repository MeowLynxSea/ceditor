#ifndef CURSOR_H
#define CURSOR_H

#include "BaseComponent.h"
#include "../utils/Color.h"
#include <windows.h>
#include <iostream>

class Cursor : public BaseComponent {
private:
    bool visibility_;
    const int cursorAttributes_ = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int lastAttributes_;
    bool posHasChanged_ = true;
    int maxLeft_, maxTop_;
    int minLeft_, minTop_;
    COORD lastPos_ = {0, 0};

public:
    Cursor() : BaseComponent(1, 1, 1, 1) { visibility_ = true; minLeft_ = minTop_ = 1; }
    Cursor(int x, int y) : BaseComponent(x, y, 1, 1) { visibility_ = true; minLeft_ = x; minTop_ = y; };
    Cursor(int x, int y, bool visibility) : BaseComponent(x, y, 1, 1) { visibility_ = visibility; minLeft_ = x; minTop_ = y; };
    ~Cursor() override = default;

    void draw() override {
        if (!visibility_) return;
        // ReadConsoleOutput
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD bufferSize = {static_cast<short>(1), static_cast<short>(1)};
        COORD bufferPos = {0, 0};
        if(posHasChanged_) {
            SMALL_RECT oldRect = {static_cast<short>(lastPos_.X - 1), static_cast<short>(lastPos_.Y - 1), static_cast<short>(lastPos_.X), static_cast<short>(lastPos_.Y)};
            CHAR_INFO buffer[1];
            if(ReadConsoleOutput(hConsole, buffer, bufferSize, bufferPos, &oldRect) == 0) {
                // std::cout << GetLastError() << std::endl;
            }
            buffer[0].Attributes = lastAttributes_;
            if(WriteConsoleOutput(hConsole, buffer, bufferSize, bufferPos, &oldRect) == 0) {
                // std::cout << GetLastError() << std::endl;
            }
        }
        SMALL_RECT rect = {static_cast<short>(left - 1), static_cast<short>(top - 1), static_cast<short>(left), static_cast<short>(top)};
        CHAR_INFO buffer[1];
        if(ReadConsoleOutput(hConsole, buffer, bufferSize, bufferPos, &rect) == 0) {
            // std::cout << GetLastError() << std::endl;
        }
        if(posHasChanged_) {
            lastAttributes_ = buffer[0].Attributes;
        }
        buffer[0].Attributes = cursorAttributes_;
        if(WriteConsoleOutput(hConsole, buffer, bufferSize, bufferPos, &rect) == 0) {
            // std::cout << GetLastError() << std::endl;
        }
        posHasChanged_ = false;
    }

    void setPosition(int x, int y) {
        posHasChanged_ = true;
        lastPos_ = {static_cast<short>(left), static_cast<short>(top)};
        BaseComponent::setPosition(x, y);
    }

    void setBounds(int maxLeft, int maxTop) {
        maxLeft_ = maxLeft;
        maxTop_ = maxTop;
    }

    void moveUp() {
        if(top > minTop_) {
            setPosition(left, top - 1);
        }
    }

    void moveDown() {
        if(top < maxTop_) {
            setPosition(left, top + 1);
        }
    }

    void moveLeft() {
        if(left > minLeft_) {
            setPosition(left - 1, top);
        }
    }

    void moveRight() {
        if(left < maxLeft_) {
            setPosition(left + 1, top);
        }
    }

    void onKeyPress(int key) override { return; }

    void setVisibility(bool visibility) {
        if(visibility == visibility_) return;
        visibility_ = visibility;
    }

    bool isVisible() { return visibility_; }
};

#endif