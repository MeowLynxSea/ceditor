#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "utils/RichText.h"

/*
#include <iostream>
#include <cassert>
#include "RichText.h"

int main() {
    // 测试默认构造函数
    RichText rt1;
    assert(rt1.plainText() == "");

    // 测试赋值运算符=
    RichText rt2;
    rt2 = "Hello";
    assert(rt2.plainText() == "Hello");

    RichText rt3;
    rt3 = StringPart{"World", COLOR_RED};
    assert(rt3.plainText() == "World");

    // 测试加法运算符+
    RichText rt4 = rt2 + rt3;
    assert(rt4.plainText() == "HelloWorld");

    RichText rt5 = rt2 + "World";
    assert(rt5.plainText() == "HelloWorld");

    RichText rt6 = rt2 + StringPart{"World", COLOR_RED};
    assert(rt6.plainText() == "HelloWorld");

    // 测试加法赋值运算符+=
    rt2 += rt3;
    assert(rt2.plainText() == "HelloWorld");

    rt2 += "World";
    assert(rt2.plainText() == "HelloWorldWorld");

    rt2 += StringPart{"World", COLOR_RED};
    assert(rt2.plainText() == "HelloWorldWorldWorld");

    // 测试substr()函数
    RichText rt7 = rt2.substr(5, 5);
    assert(rt7.plainText() == "World");
    assert(rt7.getParts()[0].color == COLOR_RED);

    // 测试text()函数
    RichText rt8 = rt2;
    assert(rt8.plainText() == "HelloWorldWorldWorld");
    assert(rt8.getParts()[0].color == COLOR_WHITE);

    // 测试plainText()函数
    std::string plain = rt2.plainText();
    assert(plain == "HelloWorldWorldWorld");

    RichText rt9 = RichText("    With some spaces before and after    ");
    RichText rt10 = rt9.substr(5, 20);
    assert(rt10.plainText() == "ith some spaces befo");

    printf("All tests passed.\n");
    return 0;
}

*/

TEST(RichText, DefaultConstructor) {
    RichText rt1;
    EXPECT_EQ(rt1.plainText(), "");
}

TEST(RichText, AssignmentOperator) {
    RichText rt2;
    rt2 = "Hello";
    EXPECT_EQ(rt2.plainText(), "Hello");

    RichText rt3;
    rt3 = StringPart{"World", COLOR_RED};
    EXPECT_EQ(rt3.plainText(), "World");
}

TEST(RichText, AdditionOperator) {
    RichText rt4 = RichText("Hello") + RichText("World");
    EXPECT_EQ(rt4.plainText(), "HelloWorld");

    RichText rt5 = RichText("Hello") + "World";
    EXPECT_EQ(rt5.plainText(), "HelloWorld");

    RichText rt6 = RichText("Hello") + StringPart{"World", COLOR_RED};
    EXPECT_EQ(rt6.plainText(), "HelloWorld");
}

TEST(RichText, AdditionAssignmentOperator) {
    RichText rt2 = RichText("Hello");
    rt2 += RichText("World");
    EXPECT_EQ(rt2.plainText(), "HelloWorld");

    rt2 += "World";
    EXPECT_EQ(rt2.plainText(), "HelloWorldWorld");

    rt2 += StringPart{"World", COLOR_RED};
    EXPECT_EQ(rt2.plainText(), "HelloWorldWorldWorld");
}

TEST(RichText, Substr) {
    RichText rt2 = RichText("HelloWorldWorldWorld", COLOR_RED);
    RichText rt7 = rt2.substr(5, 5);
    EXPECT_EQ(rt7.plainText(), "World");
    EXPECT_EQ(rt7.getParts()[0].color, COLOR_RED);

    RichText rt8 = RichText("HelloWorldWorldWorld");
    RichText rt9 = rt8.substr(5, 5);
    EXPECT_EQ(rt9.plainText(), "World");
    EXPECT_EQ(rt9.getParts()[0].color, COLOR_WHITE);

    RichText rt10 = rt8.substr(5, 20);
    EXPECT_EQ(rt10.plainText(), "WorldWorldWorld");
    EXPECT_EQ(rt10.getParts()[0].color, COLOR_WHITE);

    RichText rt11 = rt8.substr(5, 0);
    EXPECT_EQ(rt11.plainText(), "");
    EXPECT_EQ(rt11.getParts().size(), 0);
}

TEST(RichText, Text) {
    RichText rt8 = RichText("HelloWorldWorldWorld");
    EXPECT_EQ(rt8.plainText(), "HelloWorldWorldWorld");
    EXPECT_EQ(rt8.getParts()[0].color, COLOR_WHITE);
}

TEST(RichText, PlainText) {
    RichText rt2 = RichText("HelloWorldWorldWorld");
    std::string plain = rt2.plainText();
    EXPECT_EQ(plain, "HelloWorldWorldWorld");

    RichText rt9 = RichText("    With some spaces before and after    ");
    RichText rt10 = rt9.substr(5, 20);
    EXPECT_EQ(rt10.plainText(), "ith some spaces befo");
}