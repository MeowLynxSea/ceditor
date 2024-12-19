#include "Menu.h"
#include "../mystl/my_vector.h"

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cci);


    MyVector<MenuOption> ops;
    ops.push_back(MenuOption("1", "Option 1"));
    ops.push_back(MenuOption("2", "Opt 2"));
    ops.push_back(MenuOption("3", "This is Option 3"));
    Menu menu(-1, -1, RichText("Menu Title"), ops);
    menu.draw();

    while(true) {
        if (_kbhit()) {
            int scan = _getch(), opt;
            if(scan == 224) {
                opt = _getch() + 256;
            } else {
                opt = scan;
            }
            if(menu.isFocused()) {
                if(opt == 27) {
                    menu.setFocus(false);
                } else {
                    menu.onKeyPress(opt);
                }
            } else {
                if(opt == 'i') {
                    menu.setFocus(true);
                }
            }
        }

        menu.draw();
    }

    return 0;
}