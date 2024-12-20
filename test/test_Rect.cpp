#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "components/Rect.h"
#include "utils/Color.h"

TEST(RectTest, RectInit) {
    Rect rect(0, 0, 10, 10);
    EXPECT_EQ(rect.getLeft(), 0);
    EXPECT_EQ(rect.getTop(), 0);
    EXPECT_EQ(rect.getWidth(), 10);
    EXPECT_EQ(rect.getHeight(), 10);
}

TEST(RectTest, RectInitwithColor) {
    Rect rect(0, 0, 10, 10, COLOR_RED);
    EXPECT_EQ(rect.getLeft(), 0);
}

TEST(RectTest, RectSetTitle) {
    Rect rect(0, 0, 10, 10);
    rect.setTitle(RichText("test"));
    EXPECT_EQ(rect.getTitle(), "test");
}

TEST(RectTest, RectDraw) {
    Rect rect(0, 0, 10, 10);
    rect.draw();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {static_cast<short>(1), static_cast<short>(1)};
    COORD bufferPos = {0, 0};
    SMALL_RECT pos = {8, 8, 9, 9};
    CHAR_INFO buffer1[1];
    ReadConsoleOutput(hConsole, buffer1, bufferSize, bufferPos, &pos);
    EXPECT_EQ(buffer1[0].Char.AsciiChar, '-');
}