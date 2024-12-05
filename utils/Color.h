#ifndef CONSTS_H
#define CONSTS_H

#include <windows.h>
#include <wincon.h>

/*
FOREGROUND_BLUE	文本颜色包含蓝色。
FOREGROUND_GREEN	文本颜色包含绿色。
FOREGROUND_RED	文本颜色包含红色。
FOREGROUND_INTENSITY	文本颜色增强。
BACKGROUND_BLUE	背景色包含蓝色。
BACKGROUND_GREEN	背景色包含绿色。
BACKGROUND_RED	背景色包含红色。
BACKGROUND_INTENSITY	背景色增强。
*/
enum {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_PURPLE = 5,
    COLOR_YELLOW = 6,
    COLOR_WHITE = 7,
    COLOR_GRAY = 8,
    COLOR_LIGHTBLUE = 9,
    COLOR_LIGHTGREEN = 10,
    COLOR_LIGHTCYAN = 11,
    COLOR_LIGHTRED = 12,
    COLOR_LIGHTPURPLE = 13,
    COLOR_LIGHTYELLOW = 14,
    COLOR_BRIGHTWHITE = 15
};

typedef short MColor;

inline MColor getColor(int front_color, int back_color) {
    return (back_color << 4) | front_color;
}

inline WORD FrontColorToWinColor(int color) {
    switch (color) {
        case COLOR_BLACK:
            return 0;
        case COLOR_BLUE:
            return FOREGROUND_BLUE;
        case COLOR_GREEN:
            return FOREGROUND_GREEN;
        case COLOR_CYAN:
            return FOREGROUND_GREEN | FOREGROUND_BLUE;
        case COLOR_RED:
            return FOREGROUND_RED;
        case COLOR_PURPLE:
            return FOREGROUND_RED | FOREGROUND_BLUE;
        case COLOR_YELLOW:
            return FOREGROUND_RED | FOREGROUND_GREEN;
        case COLOR_WHITE:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        case COLOR_GRAY:
            return FOREGROUND_INTENSITY;
        case COLOR_LIGHTBLUE:
            return FOREGROUND_INTENSITY | FOREGROUND_BLUE;
        case COLOR_LIGHTGREEN:
            return FOREGROUND_INTENSITY | FOREGROUND_GREEN;
        case COLOR_LIGHTCYAN:
            return FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
        case COLOR_LIGHTRED:
            return FOREGROUND_INTENSITY | FOREGROUND_RED;
        case COLOR_LIGHTPURPLE:
            return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
        case COLOR_LIGHTYELLOW:
            return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
        case COLOR_BRIGHTWHITE:
            return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        default:
            return 0;
    }
}

inline int getFrontColor(MColor color) {
    return color & 0x0F;
}

inline WORD BackgroundColorToWinColor(int color) {
    switch (color) {
        case COLOR_BLACK:
            return 0;
        case COLOR_BLUE:
            return BACKGROUND_BLUE;
        case COLOR_GREEN:
            return BACKGROUND_GREEN;
        case COLOR_CYAN:
            return BACKGROUND_GREEN | BACKGROUND_BLUE;
        case COLOR_RED:
            return BACKGROUND_RED;
        case COLOR_PURPLE:
            return BACKGROUND_RED | BACKGROUND_BLUE;
        case COLOR_YELLOW:
            return BACKGROUND_RED | BACKGROUND_GREEN;
        case COLOR_WHITE:
            return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        case COLOR_GRAY:
            return BACKGROUND_INTENSITY;
        case COLOR_LIGHTBLUE:
            return BACKGROUND_INTENSITY | BACKGROUND_BLUE;
        case COLOR_LIGHTGREEN:
            return BACKGROUND_INTENSITY | BACKGROUND_GREEN;
        case COLOR_LIGHTCYAN:
            return BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
        case COLOR_LIGHTRED:
            return BACKGROUND_INTENSITY | BACKGROUND_RED;
        case COLOR_LIGHTPURPLE:
            return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
        case COLOR_LIGHTYELLOW:
            return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN;
        case COLOR_BRIGHTWHITE:
            return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        default:
            return 0;
    }
}

inline int getBackColor(MColor color) {
    return color & 0xF0;
}

#endif // CONSTS_H