#ifndef TEXT_H
#define TEXT_H

#include "BaseComponent.h"
#include <windows.h>
#include "../mystl/my_vector.h"
#include <conio.h>
#include "../utils/RichText.h"
#include <fstream>

class Text : public BaseComponent {
private:
    RichText text_;
    int viewLeft_ = 0, viewTop_ = 0;
    MyVector<RichText> lines_;
    int maxLineWidth_ = 0;

public:
    void setText(const RichText& text) {
        this->text_ = text;

        lines_.clear();
        RichText line;
        maxLineWidth_ = 0;
        // std::ofstream out("log.txt");
        for(auto part : text.getParts()) {
            if(part.text.find('\n') == std::string::npos) {
                line += part;
                // printf("Add: %s\n", part.text.c_str());
            } else {
                size_t begin = 0;
                while((begin = part.text.find('\n', 0)) != std::string::npos) {
                    line += StringPart(part.text.substr(0, begin), part.color);
                    // printf("Add: %s\n", part.text.substr(0, begin).c_str());
                    if(line.plainText() == "\n" || line.plainText() == "\r\n" || line.plainText() == "\r"){
                        line = "";
                    }
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
        if(line.plainText() == "\n") {
            line = "";
        }
        lines_.push_back(line);
        if(maxLineWidth_ < line.length()) {
            maxLineWidth_ = line.length();
        }
        // for(int i = 0; i < lines_.size(); i++) {
        //     out << lines_[i].plainText() << std::endl << "-------------------------------------------" << std::endl;
        // }
    }

    Text() : BaseComponent(0, 0, 0, 0) {
        setText(RichText());
    }

    Text(int left, int top, int width, int height) : BaseComponent(left, top, width, height) {
        setText(RichText());
    }
    Text(int left, int top, int width, int height, const RichText& text) : BaseComponent(left, top, width, height) {
        setText(text);
    }
    ~Text() override {
        lines_.clear();
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
            int currentLength = 0;
            CHAR_INFO buffer[width * 1];
            for(auto part : drawTarget.getParts()) {
                // SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
                // printf("%s", part.text.c_str());
                // SetConsoleCursorPosition(hConsole, {static_cast<short>(left + currentLength - 1), static_cast<short>(top + i - viewTop_ - 1)});
                // WriteConsoleA(hConsole, part.text.c_str(), part.text.length(), NULL, NULL);
                for(int j = 0; j < part.text.length(); j++) {
                    buffer[currentLength + j].Char.UnicodeChar = part.text[j];
                    buffer[currentLength + j].Attributes = BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color));
                }
                currentLength += part.text.length();
            }
            CONSOLE_SCREEN_BUFFER_INFO currentCSBI;
            GetConsoleScreenBufferInfo(hConsole, &currentCSBI);
            // std::string space = "";
            for(int j = 0; j < width - drawTarget.plainText().length(); j++) {
                // space += " ";
                buffer[currentLength + j].Char.UnicodeChar = ' ';
                buffer[currentLength + j].Attributes = currentCSBI.wAttributes;
            }
            // SetConsoleCursorPosition(hConsole, {static_cast<short>(left + drawTarget.plainText().length() - 1), static_cast<short>(top + i - viewTop_ - 1)});
            // WriteConsoleA(hConsole, space.c_str(), space.length(), NULL, NULL);
            SetConsoleCursorPosition(hConsole, {static_cast<short>(left), static_cast<short>(top + i - viewTop_)});
            COORD bufferSize = {static_cast<short>(width), 1};
            COORD bufferCoord = {0, 0};
            SMALL_RECT rect = {static_cast<short>(left - 1), static_cast<short>(top + i - viewTop_ - 1), static_cast<short>(left + width - 1), static_cast<short>(top + i - viewTop_ + 1)};
            WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &rect);
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