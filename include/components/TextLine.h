#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "BaseComponent.h"
#include <windows.h>
#include "../utils/RichText.h"
#include "Rect.h"
#include "Text.h"

class TextLine : public BaseComponent {
private:
    Text text_ = Text(0, 0, 0, 0);
    Rect border_ = Rect(0, 0, 0, 0);

public:
    TextLine(int left, int top, int width, int height) : BaseComponent(left, top, width, height){
        text_ = Text(left + 1, top + 1, width - 2, 1);
        border_ = Rect(left, top, width, height);
    }
    TextLine(int left, int top, int width, int height, const RichText& text) : BaseComponent(left, top, width, height){
        text_ = Text(left + 1, top + 1, width - 2, 1, text);
        border_ = Rect(left, top, width, height);
    }
    ~TextLine() override {}

    void setText(const RichText& text) {
        text_.setText(text);
    }

    RichText getText() {
        return text_.getText();
    }

    void draw() override {
        border_.draw();

        //使用渲染边框，超出屏幕边缘的区域不渲染
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        text_.draw();

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void onKeyPress(int key) override {
        //不处理按键
    }

    void setSize(int width, int height) {
        BaseComponent::setSize(width, height);
        text_.setSize(width - 2, 1);
        border_.setSize(width, height);
    }

    void setPosition(int left, int top) {
        BaseComponent::setPosition(left, top);
        text_.setPosition(left + 1, top + 1);
        border_.setPosition(left, top);
    }
};

#endif