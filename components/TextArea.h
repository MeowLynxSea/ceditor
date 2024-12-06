#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "BaseComponent.h"
#include <windows.h>
#include <vector>
#include <conio.h>
#include "../utils/RichText.h"

class TextArea : public BaseComponent {
private:
    RichText text;
    int viewLeft = 0, viewTop = 0;
    std::vector<RichText> lines;
    int maxLineWidth = 0;
    RichText title;

    int findnth(std::string str, std::string target, int n){
        if(n == 0) return -1;
        int count = 0;
        size_t begin = 0;
        while((begin = str.find(target, begin)) != std::string::npos){
            count++;
            begin += target.length();
            if(n == count){
                return begin - 1;
            }
        }
        return -2;
    }


public:
    void setText(const RichText& text) {
        this->text = text;

        lines.clear();
        RichText line;
        maxLineWidth = 0;
        for(auto part : text.getParts()) {
            if(part.text.find('\n') == std::string::npos) {
                line += part;
                // printf("Add: %s\n", part.text.c_str());
            } else {
                size_t begin = 0;
                while((begin = part.text.find('\n', begin)) != std::string::npos) {
                    line += StringPart(part.text.substr(0, begin), part.color);
                    // printf("Add: %s\n", part.text.substr(0, begin).c_str());
                    lines.push_back(line);
                    if(maxLineWidth < line.length()) {
                        maxLineWidth = line.length();
                    }
                    // printf("Push: %s\n", line.plainText().c_str());
                    line = RichText();
                    part.text = part.text.substr(begin + 1);
                    // printf("Rest: %s\n", part.text.c_str());
                }
                line += part;
                // printf("Add: %s\n", part.text.c_str());
            }
        }
        if(line.length() > 0) {
            lines.push_back(line);
            if(maxLineWidth < line.length()) {
                maxLineWidth = line.length();
            }
        }
    }

    RichText getText() {
        return text;
    }

    TextArea(int top, int left, int width, int height) : BaseComponent(top, left, width, height){
        setText(RichText());
    }
    TextArea(int top, int left, int width, int height, const RichText& text) : BaseComponent(top, left, width, height){
        setText(text);
    }
    ~TextArea() override {}

    void draw() override {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        //清空区域
        for(int i = 0; i < height && top + i < csbi.dwSize.Y; i++) {
            for(int j = 0; j < width && left + j < csbi.dwSize.X; j++) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(left + j), static_cast<short>(top + i)});
                printf(" ");
            }
        }
        //绘制边框到缓冲区
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
        
        //绘制标题
        SetConsoleCursorPosition(hConsole, {static_cast<short>(left + 1), static_cast<short>(top - 1)});
        for(auto part : title.getParts()) {
            SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
            printf("%s", part.text.c_str());
        }

        for(int i = viewTop; i < viewTop + height - 2 && i < lines.size(); i++) {
            RichText drawTarget = lines[i].substr(viewLeft, std::min(width - 2, csbi.dwSize.X - left - 2));
            SetConsoleCursorPosition(hConsole, {static_cast<short>(left), static_cast<short>(top + i - viewTop)});
            for(auto part : drawTarget.getParts()) {
                SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
                printf("%s", part.text.c_str());
            }
        }

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void setViewTop(int top) {
        this->viewTop = top;
    }

    int getViewTop() {
        return this->viewTop;
    }

    void setViewLeft(int left) {
        this->viewLeft = left;
    }

    int getViewLeft() {
        return this->viewLeft;
    }

    void moveLeft() {
        if(viewLeft > 0) {
            viewLeft--;
        }
    }

    void moveRight() {
        if(viewLeft < maxLineWidth - width + 2) {
            viewLeft++;
        }
    }

    void moveUp() {
        if(viewTop > 0) {
            viewTop--;
        }
    }

    void moveDown() {
        if(viewTop < lines.size() - height + 2) {
            viewTop++;
        }
    }

    void onKeyPress(int key) override {
        //不处理按键
    }

    void setTitle(const RichText& title) {
        this->title = title;
    }
};

#endif