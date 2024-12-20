#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "components/Cursor.h"

TEST(Cursor, CursorInit) {
    Cursor cursor;
    EXPECT_EQ(cursor.getLeft(), 1);
    EXPECT_EQ(cursor.getTop(), 1);
}

TEST(Cursor, CursorMove) {
    Cursor cursor;
    cursor.moveDown();
    cursor.moveRight();
    cursor.moveDown();
    cursor.moveLeft();
    EXPECT_EQ(cursor.getLeft(), 1);
    EXPECT_EQ(cursor.getTop(), 3);
}

TEST(Cursor, CursorMoveTo) {
    Cursor cursor;
    cursor.setPosition(3, 4);
    EXPECT_EQ(cursor.getLeft(), 3);
    EXPECT_EQ(cursor.getTop(), 4);
}

TEST(Cursor, CursorBoundaries) {
    Cursor cursor;
    cursor.setPosition(10, 10);
    cursor.setBounds(14, 14);
    cursor.moveUp();
    for(int i = 0; i < 10; i++) {
        cursor.moveRight();
    }
    EXPECT_EQ(cursor.getLeft(), 14);
    EXPECT_EQ(cursor.getTop(), 9);
}

TEST(Cursor, Draw) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {static_cast<short>(1), static_cast<short>(1)};
    COORD bufferPos = {0, 0};
    SMALL_RECT pos = {2, 3, 3, 4};
    CHAR_INFO buffer1[1], buffer2[1];
    ReadConsoleOutput(hConsole, buffer1, bufferSize, bufferPos, &pos);

    Cursor cursor;
    cursor.setPosition(3, 4);
    cursor.setVisibility(true);
    cursor.draw();

    ReadConsoleOutput(hConsole, buffer2, bufferSize, bufferPos, &pos);
    EXPECT_EQ(buffer1[0].Char.UnicodeChar, buffer2[0].Char.UnicodeChar);
    EXPECT_EQ(buffer2[0].Attributes, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}