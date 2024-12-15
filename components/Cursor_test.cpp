#include "Cursor.h"
#include <iostream>
#include <cassert>
#include <conio.h>

int main() {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            std::cout << char('a' + j);
        }
        std::cout << std::endl;
    }

    // Test case 1: Cursor is created at the origin
    Cursor cursor1;
    cursor1.draw();
    assert(cursor1.getLeft() == 1);
    assert(cursor1.getTop() == 1);

    // Test case 2: Cursor is moved to a positive coordinate
    cursor1.setPosition(5, 10);
    cursor1.draw();
    assert(cursor1.getLeft() == 5);

    cursor1.setBounds(20, 20);

    while(true) {
        if (_kbhit()) {
            char opt = _getch();
            switch(opt) {
                case 72:
                    cursor1.moveUp();
                    break;
                case 80:
                    cursor1.moveDown();
                    break;
                case 75:
                    cursor1.moveLeft();
                    break;
                case 77:
                    cursor1.moveRight();
                    break;
                case 'q':
                    return 0;
            }
            cursor1.draw();
        }
    }

    return 0;
}