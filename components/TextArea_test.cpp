#include "BaseComponent.h"
#include "TextArea.h"
#include "../utils/RichText.h"
#include <conio.h>

int main() {
    RichText richText;
    richText = "Hello, World";
    richText += StringPart(" with colors!\n", COLOR_RED);
    richText += "And more text.\n";
    richText += StringPart("And more more more text.", COLOR_GREEN);
    richText += " And more more more more more text.\n";
    richText += StringPart("And more more more more more more text.", COLOR_BLUE);
    richText += " And more more more more more more more text.\n";
    richText += StringPart("And more more more more more more more more text.\n", COLOR_YELLOW);
    richText += "And more more more more more more more more more text.\n";
    richText += StringPart("And more more more more more more more more more more text.\n", COLOR_CYAN);

    TextArea textArea(3, 3, 64, 7, richText);

    // 创建后台缓冲区
    HANDLE hBackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 清空后台缓冲区
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwBytesWritten;
    FillConsoleOutputCharacter(hBackBuffer, ' ', csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
    FillConsoleOutputAttribute(hBackBuffer, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hBackBuffer, &cci);
    SetConsoleCursorInfo(hConsole, &cci);

    textArea.setTitle(RichText("TextArea Demo", COLOR_RED));
    textArea.draw();

    while(true) {
        if (_kbhit()) {SetConsoleActiveScreenBuffer(hBackBuffer);
            char opt = _getch();
            textArea.setText(richText + StringPart("Last Key: " + std::to_string(opt), COLOR_CYAN));
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
                    SetConsoleActiveScreenBuffer(hConsole);
                    CloseHandle(hBackBuffer);
                    return 0;
            }
            
            

            // 清空后台缓冲区
            FillConsoleOutputCharacter(hBackBuffer, ' ', csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);
            FillConsoleOutputAttribute(hBackBuffer, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &dwBytesWritten);

            // 在后台缓冲区中绘制
            textArea.draw();

            // 切换到后台缓冲区，显示绘制的内容
            SetConsoleActiveScreenBuffer(hConsole);
        }
        Sleep(1);
    }

    return 0;
}