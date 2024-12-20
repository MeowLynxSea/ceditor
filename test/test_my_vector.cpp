#include "mystl/my_vector.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

TEST(MyVector, DefaultConstructor) {
    MyVector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(MyVector, ConstructorWithSize) {
    MyVector<int> v(10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(MyVector, ConstructorWithSizeAndValue) {
    MyVector<int> v(10, 5);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], 5);
    }
}

TEST(MyVector, CopyConstructor) {
    MyVector<int> v1(10, 5);
    MyVector<int> v2(v1);
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, AssignmentOperator) {
    MyVector<int> v1(10, 5);
    MyVector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, AssignmentOperatorWithDifferentSize) {
    MyVector<int> v1(10, 5);
    MyVector<int> v2(20, 10);
    v2 = v1;
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, AssignmentOperatorWithDifferentValue) {
    MyVector<int> v1(10, 5);
    MyVector<int> v2(10, 10);
    v2 = v1;
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, AssignmentOperatorWithDifferentValueAndSize) {
    MyVector<int> v1(10, 5);
    MyVector<int> v2(20, 10);
    v2 = v1;
    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, Iterator) {
    MyVector<int> v(10, 5);
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        EXPECT_EQ(*it, 5);
        i++;
    }
    EXPECT_EQ(i, 10);
}

TEST(MyVector, TestPushBack) {
    MyVector<int> v;
    v.push_back(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v[0], 5);
}

TEST(MyVector, TestPopBack) {
    MyVector<int> v(10, 5);
    v.pop_back();
    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v.capacity(), 10);
    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(v[i], 5);
    }
}

TEST(MyVector, TestPush) {
    MyVector<int> v;
    v.push(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v[0], 5);
}

TEST(MyVector, TestPop) {
    MyVector<int> v(10, 5);
    v.pop();
    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v.capacity(), 10);
    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(v[i], 5);
    }
}

TEST(MyVector, TestResize) {
    MyVector<int> v2(10, 5);
    v2.resize(20, 10);
    EXPECT_EQ(v2.size(), 20);
    EXPECT_EQ(v2.capacity(), 20);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
}

TEST(MyVector, TestResizeWithDifferentValue) {
    MyVector<int> v2(10, 5);
    v2.resize(20, 10);
    EXPECT_EQ(v2.size(), 20);
    EXPECT_EQ(v2.capacity(), 20);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], 5);
    }
    for (int i = 10; i < 20; i++) {
        EXPECT_EQ(v2[i], 10);
    }
}