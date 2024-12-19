#include "BaseComponent.h"
#include "Editor.h"
#include "../utils/RichText.h"
#include <conio.h>
#include <fstream>

int main() {
    Editor editor(2, 2, 80, 20);
    editor.setTitle("Editor Demo");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cci);

    std::ifstream file("Editor_test.cpp");
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    content = content.substr(0, content.size() - 1); // remove last newline

    editor.setRuleName("cpp");
    editor.setContent(content);

    editor.draw();

    while(true) {
        if (_kbhit()) {
            int scan = _getch(), opt;
            if(scan == 224) {
                opt = _getch() + 256;
            } else if(scan == 26) {
                opt = 26 + 512;
            } else {
                opt = scan;
            }
            if(editor.isFocused()) {
                if(opt == 27) {
                    editor.setFocus(false);
                } else {
                    editor.onKeyPress(opt);
                }
            } else {
                if(opt == 'i') {
                    editor.setFocus(true);
                }
            }
        }
    }

    return 0;
}