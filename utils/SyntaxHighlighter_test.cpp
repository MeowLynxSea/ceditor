#include "SyntaxHighlighter.h"
#include "../components/TextArea.h"

int main() {
    SyntaxHighlighter highlighter = SyntaxHighlighter("cpp");
    TextArea textArea = TextArea(1, 1, 100, 50);
    std::string rawText;
    // read in SyntaxHighlighter_test.cpp
    std::ifstream file("SyntaxHighlighter_test.cpp");
    std::string line;
    while (std::getline(file, line)) {
        rawText += line + "\n";
    }
    file.close();

    RichText richText = highlighter.highlight(rawText);

    // // 创建后台缓冲区
    // HANDLE hBackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // // 清空后台缓冲区
    // CONSOLE_SCREEN_BUFFER_INFO csbi;
    // GetConsoleScreenBufferInfo(hConsole, &csbi);
    // DWORD dwBytesWritten;
    // FillConsoleOutputCharacter(hBackBuffer, ' ', csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
    // FillConsoleOutputAttribute(hBackBuffer, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    //SetConsoleCursorInfo(hBackBuffer, &cci);
    SetConsoleCursorInfo(hConsole, &cci);

    textArea.setTitle(RichText("SyntaxHighlighter Test", COLOR_LIGHTRED));
    textArea.setText(richText);
    // textArea.setText(RichText(rawText, COLOR_WHITE));
    textArea.draw();

    while(true) {
        if (_kbhit()) {
            // SetConsoleActiveScreenBuffer(hBackBuffer);
            char opt = _getch();
            
            switch(opt) {
                case 72:
                    textArea.moveUp();
                    break;
                case 80:
                    textArea.moveDown();
                    break;
                case 75:
                    textArea.moveLeft();
                    break;
                case 77:
                    textArea.moveRight();
                    break;
                case 'q':
                    // SetConsoleActiveScreenBuffer(hConsole);
                    // CloseHandle(hBackBuffer);
                    return 0;
            }
        
            // // 清空后台缓冲区
            // FillConsoleOutputCharacter(hBackBuffer, ' ', csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
            // FillConsoleOutputAttribute(hBackBuffer, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);

            // // 在后台缓冲区中绘制
            textArea.draw();

            // // 切换到后台缓冲区，显示绘制的内容
            // SetConsoleActiveScreenBuffer(hConsole);
        }
        Sleep(1);
    }

    return 0;
}