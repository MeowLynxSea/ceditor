#include "mystl/my_deque.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

TEST(MyDequeTest, TestPushBack) {
    MyDeque<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    EXPECT_EQ(d.size(), 10);
    for(int i = 0; i < 10; ++i) {
        EXPECT_EQ(d.front(), i);
        d.pop_front();
    }
}

TEST(MyDequeTest, TestPushFront) {
    MyDeque<int> d;
    for (int i = 0; i < 100; ++i) {
        d.push_front(i);
    }
    EXPECT_EQ(d.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(d[i], 99 - i);
    }
}

TEST(MyDequeTest, TestPopBack) {
    MyDeque<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        d.pop_back();
    }
    EXPECT_EQ(d.size(), 0);
}

TEST(MyDequeTest, TestPopFront) {
    MyDeque<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        d.pop_front();
    }
    EXPECT_EQ(d.size(), 0);
}

TEST(MyDequeTest, RandomAccess) {
    MyDeque<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(d[i], i);
    }
}

TEST(MyDequeTest, Clear) {
    MyDeque<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    d.clear();
    EXPECT_EQ(d.size(), 0);
}

TEST(MyDequeTest, TestEmpty) {
    MyDeque<int> d;
    EXPECT_TRUE(d.empty());
}