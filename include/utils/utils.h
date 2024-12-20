#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <string>

void hideConsoleCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set cursor to invisible
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible = false;
    CCI.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &CCI);
}

void showConsoleCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set cursor to visible
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible = true;
    CCI.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &CCI);
}

std::string getRuleByFileName(std::string fileName) {
    std::string fileExt = fileName.substr(fileName.find_last_of(".") + 1);
    if(fileExt == "txt") {
        return "plaintext";
    } else if(fileExt == "html") {
        return "html";
    } else if(fileExt == "css") {
        return "css";
    } else if(fileExt == "js") {
        return "js";
    } else if(fileExt == "json") {
        return "json";
    } else if(fileExt == "xml") {
        return "xml";
    } else if(fileExt == "md") {
        return "markdown";
    } else if(fileExt == "py") {
        return "python";
    } else if(fileExt == "c") {
        return "c";
    } else if(fileExt == "cpp" || fileExt == "h" || fileExt == "hpp" || fileExt == "cc" || fileExt == "hh" || fileExt == "cxx" || fileExt == "hxx") {
        return "cpp";
    } else if(fileExt == "java") {
        return "java";
    } else if(fileExt == "cs") {
        return "csharp";
    } else if(fileExt == "go") {
        return "go";
    } else if(fileExt == "rs") {
        return "rust";
    } else if(fileExt == "php") {
        return "php";
    } else {
        return "plaintext"; // too much else if statements
    }
}

#endif