#ifndef RECT_H
#define RECT_H

#include "BaseComponent.h"
#include "../utils/Color.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>

class Rect : public BaseComponent {
private:
    RichText title_;
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

        std::string outputTarget = "|";
        for(int i = 1; i < height - 1 && top + i < csbi.dwSize.Y - 1; i++) {
            if(left >= 0) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left - 1), static_cast<short>(top + i - 1)});
                WriteConsoleA(hConsole, outputTarget.c_str(), outputTarget.length(), NULL, NULL);
            }
            if(left + width - 1 < csbi.dwSize.X) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + width - 2), static_cast<short>(top + i - 1)});
                WriteConsoleA(hConsole, outputTarget.c_str(), outputTarget.length(), NULL, NULL);
            }
        }
        outputTarget = "-";
        if(top >= 0) {
            for(int i = 0; i < width && left + i < csbi.dwSize.X; i++) {
                if(i > 1 && i < strlen(title_.plainText().c_str()) + 2) continue;
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + i - 1), static_cast<short>(top - 1)});
                WriteConsoleA(hConsole, outputTarget.c_str(), outputTarget.length(), NULL, NULL);
            }
        }
        if(top + height - 1 < csbi.dwSize.Y) {
            outputTarget = "";
            for(int i = 0; i < width && left + i < csbi.dwSize.X; i++) {
                outputTarget += "-";
                
            }
            SetConsoleCursorPosition(hConsole, {static_cast<short>(left - 1), static_cast<short>(top + height - 2)});
            WriteConsoleA(hConsole, outputTarget.c_str(), outputTarget.length(), NULL, NULL);
        }

        //绘制标题
        SetConsoleCursorPosition(hConsole, {static_cast<short>(left + 1), static_cast<short>(top - 1)});
        for(auto part : title_.getParts()) {
            SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
            printf("%s", part.text.c_str());
        }

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void setTitle(const RichText title) {
        title_ = title;
    }

    void onKeyPress(int key) override {
        //不处理按键
    }
};

#endif