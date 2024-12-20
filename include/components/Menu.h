#ifndef MENU_H
#define MENU_H

#include "BaseComponent.h"
#include "TextLine.h"
#include "../mystl/my_vector.h"
#include "../utils/RichText.h"
#include "../utils/Color.h"
#include <string>

struct MenuOption {
    std::string id, title;

    MenuOption(const std::string& id, const std::string& title) : id(id), title(title) {}
    MenuOption() : id(), title() {}
};

class Menu : public BaseComponent {
private:
    struct Option {
        MenuOption option;
        Text* text;

        Option(MenuOption option, Text* text) : option(option), text(text) {}
        Option() : option(), text(nullptr) {}
    };
    MyVector<Option> options_;
    int currentIndex_ = 0;
    Rect border_ = {0, 0, 0, 0};
    std::string choice_ = "";
    int defaultChoice_;

public:
    Menu(int left, int top, RichText title, MyVector<MenuOption> options, int defaultChoice = 0) : BaseComponent(left, top, 0, 0) { // set left/top to -1 to center the menu
        int maxLength = 0;
        for (int i = 0; i < options.size(); i++) {
            if (options[i].title.size() > maxLength) {
                maxLength = options[i].title.size();
            }
        }

        int width = std::max(maxLength + 2, static_cast<int>(title.plainText().length()) + 4);
        int height = options.size() + 2;

        border_.setTitle(title);
        border_.setWidth(width); border_.setHeight(height);

        // get the size of the console
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        
        if (left == -1) {
            left = (consoleWidth - width) / 2;
        }
        if (top == -1) {
            top = (consoleHeight - height) / 2;
        }
        border_.setLeft(left); border_.setTop(top);

        BaseComponent::setPosition(left, top);
        BaseComponent::setWidth(width); BaseComponent::setHeight(height);

        for (int i = 0; i < options.size(); i++) {
            // std::cout << options[i].title << " at (" << static_cast<int>(left + width / 2 - options[i].title.size() / 2) << "," << top + 1 + i << ")" << std::endl;
            options_.push_back({options[i], new Text(static_cast<int>(left + width / 2 - options[i].title.size() / 2), top + 1 + i, options[i].title.size(), 2, RichText(options[i].title, COLOR_GRAY))});
        }

        if(options_.size() > defaultChoice) {
            currentIndex_ = defaultChoice;
            defaultChoice_ = defaultChoice;
            options_[defaultChoice].text->setText(RichText(options_[defaultChoice].option.title, COLOR_WHITE));
        } else if(options_.size() > 0) {
            currentIndex_ = 0;
            defaultChoice_ = defaultChoice;            
            options_[0].text->setText(RichText(options_[0].option.title, COLOR_WHITE));
        } else {
            throw "Menu has no options";
        }
    }

    std::string getChoice() const { return choice_; }

    void draw() override {
        //清空对话框区域
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //获得缓冲区信息
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        std::string outputTarget = " ";
        for(int i = left - 1; i < left + width - 1; i++) {
            for(int j = top - 1; j < top + height - 1; j++) {
                SetConsoleCursorPosition(hConsole, {static_cast<short>(i), static_cast<short>(j)});
                WriteConsoleA(hConsole, outputTarget.c_str(), outputTarget.length(), NULL, NULL);
            }
        }

        border_.draw();
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        for (int i = 0; i < options_.size(); i++) {
            options_[i].text->draw();
        }

        SetConsoleTextAttribute(hConsole, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
    }

    void onKeyPress(int key) override {
        if(!focusStatus) return;

        if(key == 72 + 256) {
            if(currentIndex_ == 0) return;
            currentIndex_--;
        } else if(key == 80 + 256) {
            if(currentIndex_ == options_.size() - 1) return;
            currentIndex_++;
        } else if(key == 13) { // enter
            choice_ = options_[currentIndex_].option.id;
        } else if(key == 27) {
            choice_ = options_[defaultChoice_].option.id;
        }

        for (int i = 0; i < options_.size(); i++) {
            options_[i].text->setText(RichText(options_[i].text->getText().plainText(), COLOR_GRAY));
        }
        options_[currentIndex_].text->setText(RichText(options_[currentIndex_].text->getText().plainText(), COLOR_WHITE));
    }
};

#endif