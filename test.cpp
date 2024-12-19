#include "components/BaseComponent.h"
#include "components/TextLine.h"
#include "components/Editor.h"
#include "utils/RichText.h"
#include "utils/Color.h"
#include "utils/FocusManager.h"

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

    Editor mainEditor = Editor(1, 1, consoleWidth, consoleHeight - 2);
    TextLine infoBar = TextLine(1, consoleHeight - 3, consoleWidth, 3);

    mainEditor.draw();
    infoBar.draw();

    return 0;
}