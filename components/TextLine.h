#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "BaseComponent.h"
#include <windows.h>
#include "../utils/RichText.h"

class TextLine : public BaseComponent {
private:
    RichText text;

public:
    TextLine(int top, int left, int width, int height) : BaseComponent(top, left, width, height){
        text = RichText();

    }
    TextLine(int top, int left, int width, int height, const RichText& text) : BaseComponent(top, left, width, height){
        this->text = text;
    }
    ~TextLine() override {}

    void setText(const RichText& text) {
        this->text = text;
    }

    RichText getText() {
        return text;
    }

    void draw() override {
        //使用渲染边框，超出屏幕边缘的区域不渲染
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        //绘制边框到缓冲区
        for(int i = 0; i < height && top + i < csbi.dwSize.Y; i++) {
            if(left >= 0) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left - 1), static_cast<short>(top + i - 1)});
                printf("|");
            }
            if(left + width - 1 < csbi.dwSize.X) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + width - 2), static_cast<short>(top + i - 1)});
                printf("|");
            }
        }
        for(int i = 0; i < width && left + i < csbi.dwSize.X; i++) {
            if(top >= 0) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + i - 1), static_cast<short>(top - 1)});
                printf("-");
            }
            if(top + height - 1 < csbi.dwSize.Y) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + i - 1), static_cast<short>(top + height - 2)});
                printf("-");
            }
        }
        //绘制文本到缓冲区，保证不超出边框
        int textWidth = 0, i = 0;
        while(textWidth <= width - 2 && left + textWidth + 2 < csbi.dwSize.X && i < text.size()) {
            auto part = text.getParts()[i];
            SetConsoleCursorPosition(hConsole, {static_cast<short>(left + textWidth), static_cast<short>(top)});
            SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
            if(left + textWidth + part.text.length() + 2 < csbi.dwSize.X && textWidth + part.text.length() <= width - 2) {
                printf("%s", part.text.c_str());
            } else {
                printf("%s", part.text.substr(0, std::min(csbi.dwSize.X - left - textWidth - 2, width - 2 - textWidth)).c_str());
            }
            textWidth += part.text.length();
            i++;
        }

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void onKeyPress(int key) override {
        //不处理按键
    }
};

#endif