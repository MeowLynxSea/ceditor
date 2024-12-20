#include "mystl/my_skiplist.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

TEST(MySkipListTest, TestInsert) {
    SkipList<int, int> sl;
    for (int i = 0; i < 10; ++i) {
        sl.insert(i, i);
    }
    EXPECT_EQ(sl.size(), 10);
}

TEST(MySkipListTest, TestFind) {
    SkipList<int, int> sl;
    for (int i = 0; i < 10; ++i) {
        sl.insert(i, i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(sl.find(i, i));
    }
    for (int i = 10; i < 20; ++i) {
        EXPECT_FALSE(sl.find(i, i));
    }
}

TEST(MySkipListTest, TestClear) {
    SkipList<int, int> sl;
    for (int i = 0; i < 10; ++i) {
        sl.insert(i, i);
    }
    sl.clear();
    EXPECT_TRUE(sl.empty());
}