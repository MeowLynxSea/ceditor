#ifndef RICHTEXT_H
#define RICHTEXT_H

#include "Color.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <windows.h>

struct StringPart {
    std::string text;
    MColor color;

    StringPart(const std::string& t, const MColor& c) : text(t), color(c) {}
    StringPart(const std::string& t) : text(t), color(getColor(COLOR_WHITE, COLOR_BLACK)) {}
};

class RichText {
private:
    std::vector<StringPart> parts;

    void print() const {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        for(const auto& part : parts) {
            std::cout << "[" << part.color << "] ";
            SetConsoleTextAttribute(handle, BackgroundColorToWinColor(getBackColor(part.color)) | FrontColorToWinColor(getFrontColor(part.color)));
            std::cout << part.text;
            SetConsoleTextAttribute(handle, BackgroundColorToWinColor(COLOR_BLACK) | FrontColorToWinColor(COLOR_WHITE));
            std::cout << std::endl;
        }
    }

    void clearEmptyParts() {
        parts.erase(std::remove_if(parts.begin(), parts.end(), [](const StringPart& part) {
            return part.text.empty();
        }), parts.end());
    }

public:
    // 默认构造函数，初始化为一段默认黑底白字的文本
    RichText() {
        parts.push_back({""});
    }

    // 重载运算符=
    RichText& operator=(const RichText& other) {
        parts = other.parts;
        clearEmptyParts();
        return *this;
    }
    RichText& operator=(const std::string& other) {
        parts.clear();
        parts.push_back({other});
        clearEmptyParts();
        return *this;
    }
    RichText& operator=(const StringPart& other) {
        parts.clear();
        parts.push_back(other);
        clearEmptyParts();
        return *this;
    }

    // 重载运算符+
    RichText operator+(const RichText& other) const {
        RichText result = *this;
        result.parts.insert(result.parts.end(), other.parts.begin(), other.parts.end());
        result.clearEmptyParts();
        return result;
    }
    RichText operator+(const std::string& other) const {
        RichText result = *this;
        result.parts.push_back({other});
        result.clearEmptyParts();
        return result;
    }
    RichText operator+(const StringPart& other) const {
        RichText result = *this;
        result.parts.push_back(other);
        result.clearEmptyParts();
        return result;
    }

    // 重载运算符+=
    RichText& operator+=(const RichText& other) {
        parts.insert(parts.end(), other.parts.begin(), other.parts.end());
        clearEmptyParts();
        return *this;
    }
    RichText& operator+=(const std::string& other) {
        parts.push_back({other});
        clearEmptyParts();
        return *this;
    }
    RichText& operator+=(const StringPart& other) {
        parts.push_back(other);
        clearEmptyParts();
        return *this;
    }

    // substr()函数，保留原颜色
    RichText substr(size_t start, size_t length) const {
        RichText result;
        int s = 0, i = 0;
        while(s + parts[i].text.length() < start) {
            s += parts[i].text.length();
            i++;
        }
        int t_start = start - s;
        int t_length = length;
        while(t_length > 0 && i < parts.size()) {
            if(t_start > 0) {
                result += StringPart(parts[i].text.substr(t_start), parts[i].color);
                t_length -= parts[i].text.length() - t_start;
                t_start = 0;
            } else {
                if(t_length < parts[i].text.length()) {
                    result += StringPart(parts[i].text.substr(0, t_length), parts[i].color);
                    t_length = 0;
                } else {
                    result += StringPart(parts[i].text, parts[i].color);
                    t_length -= parts[i].text.length();
                }
            }
            i++;
        }
        result.clearEmptyParts();
        // result.print();
        return result;
    }

    std::vector<StringPart> getParts() const {
        return parts;
    }

    // plainText()函数，返回连接后的文本内容，不包括颜色
    std::string plainText() const {
        std::string result;
        for (const auto& part : parts) {
            result += part.text;
        }
        return result;
    }

    int size() const {
        return parts.size();
    }

    int length() const {
        int result = 0;
        for (const auto& part : parts) {
            result += part.text.length();
        }
        return result;
    }
};


#endif