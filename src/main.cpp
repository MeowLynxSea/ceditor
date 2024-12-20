#include "components/BaseComponent.h"
#include "components/Editor.h"
#include "components/TextLine.h"
#include "components/Menu.h"
#include "utils/RichText.h"
#include "utils/Color.h"
#include "utils/utils.h"

int consoleWidth, consoleHeight;
HANDLE hConsole;

int main(int argc, char* argv[]) {
    if(argc == 1) {
        std::cout << "Usage: ceditor [file]" << std::endl;
        return 1;
    }

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    hideConsoleCursor();

    Editor mainEditor = Editor(1, 1, consoleWidth - 1, consoleHeight - 3);
    TextLine infoBar = TextLine(1, consoleHeight - 3, consoleWidth - 1, 3);

    infoBar.setText(RichText("Loading..."));
    mainEditor.draw();
    infoBar.draw();

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::string ErrorMsg = "[ERROR] Cannot open file: " + std::string(argv[1]);
        infoBar.setText(RichText(ErrorMsg, COLOR_LIGHTRED));
        infoBar.draw();
        showConsoleCursor();
        return 1;
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    content = content.substr(0, content.size() - 1); // remove last newline
    infoBar.setText(RichText("File loaded: " + std::to_string(content.size()) + " characters. Press 'i' to enter insert mode.", COLOR_GREEN));

    mainEditor.setRuleName(getRuleByFileName(argv[1]));
    mainEditor.setContent(content, true);

    mainEditor.setFocus(false);

    mainEditor.draw();
    infoBar.draw();

    while(true) {
        if (_kbhit()) {
            int scan = _getch(), opt;
            if(scan == 224) {
                opt = _getch() + 256;
            } else if(scan == 26 || scan == 25) {
                opt = scan + 512;
            } else {
                opt = scan;
            }
            if(mainEditor.isFocused()) {
                if(opt == 27) {
                    mainEditor.setFocus(false);
                    if(mainEditor.isChanged()) {
                        infoBar.setText(RichText("[MODIFIED] ", COLOR_YELLOW) + RichText(std::to_string(mainEditor.getContent().size()) + " characters. Press 'i' to enter insert mode."));
                    } else {
                        infoBar.setText(RichText(std::to_string(mainEditor.getContent().size()) + " characters. Press 'i' to enter insert mode."));
                    }
                } else {
                    mainEditor.onKeyPress(opt);
                    if(mainEditor.isChanged()) {
                        infoBar.setText(RichText("[MODIFIED] ", COLOR_YELLOW) + RichText("Insert mode. Press ESC to exit."));
                    } else {
                        infoBar.setText(RichText("Insert mode. Press ESC to exit."));
                    }
                }
            } else {
                if(opt == 'i') {
                    infoBar.setText(RichText("Insert mode. Press ESC to exit."));
                    mainEditor.setFocus(true);
                } else if(opt == 256 + 72) {
                    mainEditor.moveViewUp();
                } else if(opt == 256 + 80) {
                    mainEditor.moveViewDown();
                } else if(opt == 256 + 75) {
                    mainEditor.moveViewLeft();
                } else if(opt == 256 + 77) {
                    mainEditor.moveViewRight();
                } else if(opt == 27) {
                    if(mainEditor.isChanged()) {
                        infoBar.setText(RichText("[MODIFIED] ", COLOR_YELLOW) + RichText("Exiting..."));
                        infoBar.draw();
                        MyVector<MenuOption> ops;
                        ops.push_back(MenuOption("save_and_exit", "Save and exit"));
                        ops.push_back(MenuOption("exit_without_save", "Just exit"));
                        ops.push_back(MenuOption("cancel", "Cancel"));
                        Menu menu = Menu(-1, -1, std::string("Are you sure to exit?"), ops, 2);
                        menu.draw();
                        menu.setFocus(true);
                        while(menu.getChoice() == "") {
                            if(_kbhit()) {
                                int scan = _getch(), opt;
                                if(scan == 224) {
                                    opt = _getch() + 256;
                                } else if(scan == 26 || scan == 25) {
                                    opt = scan + 512;
                                } else {
                                    opt = scan;
                                }
                                menu.onKeyPress(opt);
                                menu.draw();
                            }
                        }
                        if(menu.getChoice() == "save_and_exit") {
                            std::ofstream file(argv[1]);
                            file << mainEditor.getContent();
                            file.close();
                            infoBar.setText(RichText("File saved. Exiting...", COLOR_GREEN));
                            return 0;
                        } else if(menu.getChoice() == "exit_without_save") {
                            infoBar.setText(RichText("Exiting...", COLOR_GREEN));
                            return 0;
                        } else if(menu.getChoice() == "cancel") {
                            infoBar.setText(RichText("[MODIFIED] ", COLOR_YELLOW) + RichText("Canceled. Press 'i' to enter insert mode."));
                        }
                        infoBar.draw();
                    } else {
                        infoBar.setText(RichText("Exiting..."));
                        infoBar.draw();
                        MyVector<MenuOption> ops;
                        ops.push_back(MenuOption("confirm", "Yes"));
                        ops.push_back(MenuOption("cancel", "Cancel"));
                        Menu menu = Menu(-1, -1, std::string("Are you sure to exit?"), ops, 1);
                        menu.draw();
                        menu.setFocus(true);
                        while(menu.getChoice() == "") {
                            if(_kbhit()) {
                                int scan = _getch(), opt;
                                if(scan == 224) {
                                    opt = _getch() + 256;
                                } else if(scan == 26 || scan == 25) {
                                    opt = scan + 512;
                                } else {
                                    opt = scan;
                                }
                                menu.onKeyPress(opt);
                                menu.draw();
                            }
                        }
                        if(menu.getChoice() == "confirm") {
                            infoBar.setText(RichText("Exiting...", COLOR_GREEN));
                            return 0;
                        } else if(menu.getChoice() == "cancel") {
                            infoBar.setText(RichText("Canceled. Press 'i' to enter insert mode."));
                        }
                        infoBar.draw();
                    }
                }
            }
            mainEditor.draw();
            infoBar.draw();
        }

        // check windows resize
        if(GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            if(consoleWidth != csbi.srWindow.Right - csbi.srWindow.Left + 1 || consoleHeight != csbi.srWindow.Bottom - csbi.srWindow.Top + 1) {
                consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                mainEditor.setSize(consoleWidth - 1, consoleHeight - 3);
                infoBar.setSize(consoleWidth - 1, 3);
                infoBar.setPosition(1, consoleHeight - 3);
                system("cls");
                mainEditor.draw();
                infoBar.draw();
            }
        }
    }

    return 0;
}