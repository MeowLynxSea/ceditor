#ifndef TEXT_H
#define TEXT_H

#include "BaseComponent.h"
#include <windows.h>
#include <vector>
#include <conio.h>
#include "../utils/RichText.h"

class Text : public BaseComponent {
private:
    RichText text_;
    int viewLeft_ = 0, viewTop_ = 0;
    std::vector<RichText> lines_;
    int maxLineWidth_ = 0;

public:
    Text(int top, int left, int width, int height) : BaseComponent(top, left, width, height) {
        text_ = RichText();
    }
    Text(int top, int left, int width, int height, const RichText& text) : BaseComponent(top, left, width, height) {
        text_ = text;
    }
    ~Text() override {
        lines_.clear();
    }

    void setText(const RichText& text) {
        this->text_ = text;

        lines_.clear();
        RichText line;
        maxLineWidth_ = 0;
        for(auto part : text.getParts()) {
            if(part.text.find('\n') == std::string::npos) {
                line += part;
                // printf("Add: %s\n", part.text.c_str());
            } else {
                size_t begin = 0;
                while((begin = part.text.find('\n', begin)) != std::string::npos) {
                    line += StringPart(part.text.substr(0, begin), part.color);
                    // printf("Add: %s\n", part.text.substr(0, begin).c_str());
                    lines_.push_back(line);
                    if(maxLineWidth_ < line.length()) {
                        maxLineWidth_ = line.length();
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
            lines_.push_back(line);
            if(maxLineWidth_ < line.length()) {
                maxLineWidth_ = line.length();
            }
        }
    }

    RichText getText() {
        return text_;
    }

    void draw() override {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        for(int i = viewTop_; i < viewTop_ + height && i < lines_.size(); i++) {
            RichText drawTarget = lines_[i].substr(viewLeft_, std::min(width, csbi.dwSize.X - left));
            SetConsoleCursorPosition(hConsole, {static_cast<short>(left - 1), static_cast<short>(top + i - viewTop_ - 1)});
            for(auto part : drawTarget.getParts()) {
                SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
                printf("%s", part.text.c_str());
            }
            CONSOLE_SCREEN_BUFFER_INFO currentCSBI;
            GetConsoleScreenBufferInfo(hConsole, &currentCSBI);
            for(int cx = currentCSBI.dwCursorPosition.X; cx < left + width - 1; cx++) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(cx), static_cast<short>(currentCSBI.dwCursorPosition.Y)});
                printf(" ");
            }
        }
    }

    void setViewTop(int vtop) {
        this->viewTop_ = vtop;
    }

    int getViewTop() {
        return this->viewTop_;
    }

    void setViewLeft(int vleft) {
        this->viewLeft_ = vleft;
    }

    int getViewLeft() {
        return this->viewLeft_;
    }

    int getMaxLineWidth() {
        return this->maxLineWidth_;
    }

    int getMaxLineCount() {
        return this->lines_.size();
    }

    void onKeyPress(int key) override {}
};

#endif // TEXT_H