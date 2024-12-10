#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "BaseComponent.h"
#include <windows.h>
#include <vector>
#include <conio.h>
#include "../utils/RichText.h"
#include "Rect.h"
#include "Text.h"

class TextArea : public BaseComponent {
private:
    Text text_ = Text(0, 0, 0, 0);
    RichText title_;
    Rect border_ = Rect(0, 0, 0, 0);

public:
    TextArea(int top, int left, int width, int height) : BaseComponent(top, left, width, height){
        border_ = Rect(left, top, width, height);
        text_ = Text(left + 1, top + 1, width - 2, height - 2);
        text_.setText(RichText());
    }
    TextArea(int top, int left, int width, int height, const RichText& text) : BaseComponent(top, left, width, height){
        border_ = Rect(left, top, width, height);
        text_ = Text(left + 1, top + 1, width - 2, height - 2);
        text_.setText(text);
    }
    ~TextArea() override {}

    void draw() override {
        border_.draw();

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        //绘制标题
        SetConsoleCursorPosition(hConsole, {static_cast<short>(left + 1), static_cast<short>(top - 1)});
        for(auto part : title_.getParts()) {
            SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
            printf("%s", part.text.c_str());
        }

        text_.draw();

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void setText(const RichText& newText) {
        text_.setText(newText);
    }

    void moveLeft() {
        if(text_.getViewLeft() > 0) {
            text_.setViewLeft(text_.getViewLeft() - 1);
        }
    }

    void moveRight() {
        if(text_.getViewLeft() < text_.getMaxLineWidth() - width + 2) {
            text_.setViewLeft(text_.getViewLeft() + 1);
        }
    }

    void moveUp() {
        if(text_.getViewTop() > 0) {
            text_.setViewTop(text_.getViewTop() - 1);
        }
    }

    void moveDown() {
        if(text_.getViewTop() < text_.getMaxLineCount() - height + 2) {
            text_.setViewTop(text_.getViewTop() + 1);
        }
    }

    void onKeyPress(int key) override {
        //不处理按键
    }

    void setTitle(const RichText& newTitle) {
        this->title_ = newTitle;
    }
};

#endif