#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "components/Menu.h"
#include "mystl/my_vector.h"

TEST(Menu, Draw) {
    MyVector<MenuOption> ops;
    ops.push_back(MenuOption("1", "Option 1"));
    ops.push_back(MenuOption("2", "Opt 2"));
    ops.push_back(MenuOption("3", "This is Option 3"));
    Menu menu(-1, -1, RichText("Menu Title"), ops);
    menu.draw();
}

TEST(Menu, Slection) {
    MyVector<MenuOption> ops;
    ops.push_back(MenuOption("1", "Option 1"));
    ops.push_back(MenuOption("2", "Opt 2"));
    ops.push_back(MenuOption("3", "This is Option 3"));
    Menu menu(-1, -1, RichText("Menu Title"), ops);
    menu.draw();
    menu.onKeyPress(256 + 72);
    menu.onKeyPress(13);
    EXPECT_EQ(menu.getChoice(), "");
    menu.onKeyPress(256 + 80);
    menu.onKeyPress(13);
    EXPECT_EQ(menu.getChoice(), "");

    menu.setFocus(true);

    menu.onKeyPress(256 + 80);
    EXPECT_EQ(menu.getChoice(), "");
    menu.onKeyPress(13);
    EXPECT_EQ(menu.getChoice(), "2");
}