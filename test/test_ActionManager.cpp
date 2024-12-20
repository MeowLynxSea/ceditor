#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "utils/ActionManager.h"

TEST(ActionManagerTest, ActionManagerInit) {
    ActionManager manager;
    EXPECT_EQ(manager.getContent().length(), 0);
    std::string str = "test";
    manager.setOriginContent(str);
}

TEST(ActionManagerTest, ActionManagerUndo) {
    ActionManager manager;
    std::string str = "test";
    manager.setOriginContent(str);
    EXPECT_EQ(manager.getContent(), str);
    EXPECT_EQ(manager.undo(), false);

    manager.updateContent("test2");
    EXPECT_EQ(manager.getContent(), "test2");
    EXPECT_EQ(manager.undo(), true);
    EXPECT_EQ(manager.getContent(), str);
}

TEST(ActionManagerTest, ActionManagerRedo) {
    ActionManager manager;
    std::string str = "test";
    manager.setOriginContent(str);
    EXPECT_EQ(manager.getContent(), str);
    EXPECT_EQ(manager.redo(), false);

    manager.updateContent("test2");
    EXPECT_EQ(manager.getContent(), "test2");
    EXPECT_EQ(manager.undo(), true);
    EXPECT_EQ(manager.getContent(), str);
    EXPECT_EQ(manager.redo(), true);
    EXPECT_EQ(manager.getContent(), "test2");
}

TEST(ActionManagerTest, ActionManagerCalculateEditActions) {
    ActionManager manager;
    std::string str = "i love you";
    MyVector<EditAction> v;
    v = manager.calculateEditActions(str, "YOU love ME");
    for(int i = 0; i < v.size(); i++) {
        if(v[i].type == EditActiontype::Insert) {
            str.insert(v[i].pos, v[i].content);
        } else if(v[i].type == EditActiontype::Delete) {
            str.erase(v[i].pos, v[i].content.size());
        }
    }
    EXPECT_EQ(str, "YOU love ME");
}