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
