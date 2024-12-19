#include "components/BaseComponent.h"
#include "components/Editor.h"
#include "components/TextLine.h"
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
    // Set cursor to invisible
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cci);

    Editor mainEditor = Editor(1, 1, consoleWidth - 1, consoleHeight - 3);
    TextLine infoBar = TextLine(1, consoleHeight - 3, consoleWidth - 1, 3);

    infoBar.setText(RichText("Welcome to CEditor!"));
    mainEditor.draw();
    infoBar.draw();
    getchar();

    std::ifstream file(argv[1]);
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    content = content.substr(0, content.size() - 1); // remove last newline

    mainEditor.setRuleName("cpp");
    mainEditor.setContent(content, true);

    clock_t start = clock();
    int frames = 0;
    while(true) {
        clock_t end = clock();
        if(end - start >= 1000) {
            infoBar.setText("FPS: " + std::to_string(frames));
            start = end;
            frames = 0;
        }
        frames++;
        mainEditor.draw();
        infoBar.draw();
    }

    getchar();

    return 0;
}