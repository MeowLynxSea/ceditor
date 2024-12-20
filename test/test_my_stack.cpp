#include "mystl/my_stack.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

TEST(MyStackTest, TestPush) {
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(3, stack.size());
    EXPECT_EQ(3, stack.top());
}

TEST(MyStackTest, TestPop) {
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    EXPECT_EQ(2, stack.size());
    EXPECT_EQ(2, stack.top());
}

TEST(MyStackTest, TestEmpty) {
    MyStack<int> stack;
    EXPECT_TRUE(stack.empty());
    stack.push(1);
    EXPECT_FALSE(stack.empty());
    stack.pop();
    EXPECT_TRUE(stack.empty());
}