#include "mystl/my_list.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

TEST(MyListTest, TestPushBack) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 5);
}

TEST(MyListTest, TestPushFront) {
  MyList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.push_front(5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 1);
}

TEST(MyListTest, TestPopBack) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.pop_back();
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.back(), 4);

  list.pop_back();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.back(), 3);
}

TEST(MyListTest, TestPopFront) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.pop_front();
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), 2);

  list.pop_front();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 3);
}

TEST(MyListTest, TestInsert) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.insert(3, 6);

  EXPECT_EQ(list.size(), 6);
}

TEST(MyListTest, TestErase) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.erase(3);

  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 5);

  list.erase(0);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 5);
}

TEST(MyListTest, TestClear) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.clear();

  EXPECT_EQ(list.size(), 0);
}

TEST(MyListTest, TestIterator) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  MyList<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(MyListTest, TestEraseforIterator) {
  MyList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  MyList<int>::iterator it = list.begin();
  ++it;
  list.erase(it);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*++list.begin(), 3);

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(*list.begin(), 3);
}