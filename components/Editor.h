#ifndef EDITOR_H
#define EDITOR_H

#include "BaseComponent.h"
#include "TextArea.h"
#include "Cursor.h"
#include "../utils/SyntaxHighlighter.h"
#include "../utils/ActionManager.h"
#include "../utils/RichText.h"
#include <string>

class Editor : public BaseComponent {
private:
    TextArea textArea_ = TextArea(0, 0, 0, 0);
    Cursor cursor_ = Cursor(0, 0, false);
    std::string content_;
    RichText coloredContent_;
    std::string ruleName_;
    MyVector<std::string> lineedContent_;
    ActionManager actionmanager_;
    enum class InputStatus {
        Insert,
        Delete,
        Command
    };
    InputStatus inputstatus_;
    static const int MAX_DIVISION_TIME = 1200; // 1.2s
    int lastInputTime_ = 0;

    MyVector<std::string> split(std::string content) {
        MyVector<std::string> lineedContent;
        std::string tempStr = content_ + "\n";
        size_t pos = tempStr.find("\n");
        lineedContent.clear();
        while(pos != std::string::npos) {
            lineedContent.push_back(tempStr.substr(0, pos));
            tempStr = tempStr.substr(pos + 1);
            pos = tempStr.find("\n");
        }
        return lineedContent;
    }

    std::string assemble(MyVector<std::string> lineedContent) {
        std::string content = "";
        for(auto line : lineedContent) {
            content += line + "\n";
        }
        return content.substr(0, content.size() - 1);
    }

public:
    Editor(int left, int top, int width, int height) : BaseComponent(left, top, width, height) {
        textArea_ = TextArea(left, top, width, height);
        cursor_.setPosition(left + 1, top + 1);
        cursor_.setBounds(left + width - 2, top + height - 2);
        content_ = "";
        cursor_.setVisibility(false);
        actionmanager_.setOriginContent(content_);
        inputstatus_ = InputStatus::Insert;
    };

    void setRuleName(std::string ruleName) { ruleName_ = ruleName; }
    std::string getRuleName() { return ruleName_; }

    void setContent(std::string content, bool firstTime = false) {
        content_ = content;
        coloredContent_ = SyntaxHighlighter(ruleName_).highlight(content_);
        textArea_.setText(coloredContent_);
        lineedContent_ = split(content_);
        if(firstTime) actionmanager_.setOriginContent(content_);
    }

    std::string getContent() { return content_; }

    void setTitle(std::string title) {
        textArea_.setTitle(RichText(title));
    }
    void setTitle(RichText title) {
        textArea_.setTitle(title);
    }

    void draw() override {
        textArea_.draw();
        cursor_.draw();
    }

    void moveUp(int step = 1) {
        for(int i = 0; i < step; i++)
        if(cursor_.getTop() == top + 1) {
            textArea_.moveUp();
        } else {
            cursor_.moveUp();
        }
    }

    void moveDown(int step = 1) {
        for(int i = 0; i < step; i++)
        if(cursor_.getTop() == top + height - 2) {
            textArea_.moveDown();
        } else {
            cursor_.moveDown();
        }
    }

    void moveLeft(int step = 1) {
        for(int i = 0; i < step; i++)
        if(cursor_.getLeft() == left + 1) {
            textArea_.moveLeft();
        } else {
            cursor_.moveLeft();
        }
    }

    void moveRight(int step = 1) {
        for(int i = 0; i < step; i++)
        if(cursor_.getLeft() == left + width - 2) {
            textArea_.moveRight();
        } else {
            cursor_.moveRight();
        }
    }

    void setFocus(bool focusStatus) {
        BaseComponent::setFocus(focusStatus);
        cursor_.setVisibility(focusStatus);
    }

    void onKeyPress(int key) override {
        if(!focusStatus) return;

        int currentLine = cursor_.getTop() - top - 1 + textArea_.getViewTop();
        int currentChar = cursor_.getLeft() - left - 1 + textArea_.getViewLeft();
        int lineLength = lineedContent_[currentLine].size();

        if(key >= 256 && key < 512) {
            if(inputstatus_ != InputStatus::Command) {
                inputstatus_ = InputStatus::Command;
                actionmanager_.updateContent(content_);
            }
            if (key == 72 + 256) { // up
                moveUp();
            } else if(key == 80 + 256) { // down
                moveDown();
            } else if(key == 75 + 256) { // left
                moveLeft();
            } else if(key == 77 + 256) { // right
                moveRight();
            }
        } else {
            if(key == 224) return;
            if(currentChar > lineLength) {
                for(int i = 0; i < currentChar - lineLength; i++) {
                    moveLeft();
                }
                currentChar = lineLength;
            }

            if(key == 8) { // backspace
                if(inputstatus_ != InputStatus::Delete) {
                    inputstatus_ = InputStatus::Delete;
                    // std::string rst = actionmanager_.updateContent(getContent()) ? "success" : "fail";
                    // MessageBoxA(NULL, rst.c_str(), "Update Content", MB_OK);
                }
                // 如果是第一个字符，则把当前行内容加到上一行末尾
                if(currentChar == 0) {
                    if(currentLine > 0) {
                        //移动光标到上一行末尾
                        moveUp();
                        for(int i = 0; i < lineedContent_[currentLine - 1].size(); i++) {
                            moveRight();
                        }
                        lineedContent_[currentLine - 1] += lineedContent_[currentLine];
                        lineedContent_.erase(lineedContent_.begin() + currentLine);
                        setContent(assemble(lineedContent_));
                    }
                } else {
                    //否则把当前行内容减去一个字符
                    moveLeft();
                    lineedContent_[currentLine] = lineedContent_[currentLine].substr(0, currentChar - 1) + lineedContent_[currentLine].substr(currentChar);
                    setContent(assemble(lineedContent_));
                }
            } else if(key == 127 || key == 83 + 256) { // delete
                if(inputstatus_ != InputStatus::Delete) {
                    inputstatus_ = InputStatus::Delete;
                    actionmanager_.updateContent(content_);
                }
                if(currentChar == lineLength) {
                    if(currentLine < lineedContent_.size() - 1) {
                        lineedContent_[currentLine] += lineedContent_[currentLine + 1];
                        lineedContent_.erase(lineedContent_.begin() + currentLine + 1);
                        setContent(assemble(lineedContent_));
                    }  
                } else {
                    //否则把当前行内容减去一个字符
                    lineedContent_[currentLine] = lineedContent_[currentLine].substr(0, currentChar) + lineedContent_[currentLine].substr(currentChar + 1);
                    setContent(assemble(lineedContent_));
                }
            } else if(key == 13) { // enter 
                if(inputstatus_ != InputStatus::Insert) {
                    inputstatus_ = InputStatus::Insert;
                    actionmanager_.updateContent(content_);
                }
                lineedContent_[currentLine].insert(currentChar, "\n");
                setContent(assemble(lineedContent_));
                moveDown();
                for(int i = 0; i < currentChar; i++) {
                    moveLeft();
                }
            } else if(key >= 512 && key < 768) { // ctrl + 
                if(inputstatus_ != InputStatus::Command) {
                    inputstatus_ = InputStatus::Command;
                    actionmanager_.updateContent(content_);
                }
                key -= 512;
                switch (key) {
                    case 26: // ctrl + z
                        actionmanager_.undo();
                        setContent(actionmanager_.getContent());
                        break;
                    case 25: // ctrl + y
                        actionmanager_.redo();
                        setContent(actionmanager_.getContent());
                        break;
                }
            } else {
                if(inputstatus_ != InputStatus::Insert) {
                    inputstatus_ = InputStatus::Insert;
                    actionmanager_.updateContent(content_);
                }
                if(key == 32 || key == 9) { // space
                    actionmanager_.updateContent(content_);
                }
                if(key == 9) { // tab
                    lineedContent_[currentLine].insert(currentChar, "    ");
                    moveRight(3);
                } else {
                    lineedContent_[currentLine].insert(currentChar, 1, key);
                }
                setContent(assemble(lineedContent_));
                moveRight();
            }
        }
    }
};

#endif