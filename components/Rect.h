#ifndef RECT_H
#define RECT_H

#include "BaseComponent.h"
#include "../utils/Color.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>

class Rect : public BaseComponent {
private:
    MColor color_ = COLOR_WHITE;

public:
    Rect(int top, int left, int width, int height) : BaseComponent(top, left, width, height){
        color_ = getColor(COLOR_WHITE, COLOR_BLACK);
    }
    Rect(int top, int left, int width, int height, const MColor color) : BaseComponent(top, left, width, height){
        color_ = color;
    }
    ~Rect() override {}

    void draw() override {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(color_)) | FrontColorToWinColor(getFrontColor(color_)));

        for(int i = 1; i < height - 1 && top + i < csbi.dwSize.Y - 1; i++) {
            if(left >= 0) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left - 1), static_cast<short>(top + i - 1)});
                putchar('|');
            }
            if(left + width - 1 < csbi.dwSize.X) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + width - 2), static_cast<short>(top + i - 1)});
                putchar('|');
            }
        }
        for(int i = 0; i < width && left + i < csbi.dwSize.X; i++) {
            if(top >= 0) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + i - 1), static_cast<short>(top - 1)});
                putchar('-');
            }
            if(top + height - 1 < csbi.dwSize.Y) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + i - 1), static_cast<short>(top + height - 2)});
                putchar('-');
            }
        }

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void onKeyPress(int key) override {
        //不处理按键
    }
};

#endif