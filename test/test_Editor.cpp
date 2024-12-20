#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "components/Editor.h"

std::string originalText = "#include <iostream>\n\
using namespace std;\n\
\
int main() {\n\
    cout << \"Hello, world!\"\n\
    return 0;\n\
}";

TEST(Editor, TestEditorInit) {
    Editor editor = Editor(0, 0, 0, 0);
    EXPECT_EQ(editor.getContent(), "");
}

TEST(Editor, TestEditorSetAndGetContent) {
    Editor editor = Editor(0, 0, 0, 0);
    editor.setContent(originalText);
    EXPECT_EQ(editor.getContent(), originalText);
}

TEST(Editor, TestEditorSetRuleName) {
    Editor editor = Editor(0, 0, 0, 0);
    editor.setRuleName("cpp");
    EXPECT_EQ(editor.getRuleName(), "cpp");
}

TEST(Editor, TestEditorDraw) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText);
    editor.setRuleName("cpp");
    editor.draw();
}

TEST(Editor, TestEditorMove) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText);
    editor.setRuleName("cpp");
    editor.setPosition(5, 5);
    editor.draw();
    EXPECT_EQ(editor.getLeft(), 5);
    EXPECT_EQ(editor.getTop(), 5);
}

TEST(Editor, TestEditorResize) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText);
    editor.setRuleName("cpp");
    editor.setSize(20, 20);
    editor.draw();
    EXPECT_EQ(editor.getWidth(), 20);
    EXPECT_EQ(editor.getHeight(), 20);
}

TEST(Editor, TestEditorScroll) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText);
    editor.setRuleName("cpp");
    editor.moveLeft(); 
    editor.moveUp();
    editor.moveRight(4);
    editor.moveDown(4);
    editor.draw();
}

TEST(Editor, TestEditorViewMove) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText);
    editor.setRuleName("cpp");
    editor.moveViewLeft();
    editor.moveViewUp();
    editor.moveViewRight();
    editor.moveViewDown();
    editor.draw();
}

TEST(Editor, EmulateEdit) {
    Editor editor = Editor(0, 0, 10, 10);
    editor.setContent(originalText, true);
    editor.setRuleName("cpp");
    EXPECT_FALSE(editor.isChanged());
    editor.onKeyPress('h');
    EXPECT_FALSE(editor.isChanged());
    EXPECT_EQ(editor.getContent(), originalText);
    
    editor.setFocus(true);
    editor.onKeyPress('h');
    editor.onKeyPress(32);
    EXPECT_EQ(editor.getContent(), "h " + originalText);
    EXPECT_TRUE(editor.isChanged());
    editor.onKeyPress('b');
    EXPECT_EQ(editor.getContent(), "h b" + originalText);
    editor.onKeyPress('c');
    EXPECT_EQ(editor.getContent(), "h bc" + originalText);
    editor.onKeyPress(512 + 26);
    EXPECT_EQ(editor.getContent(), "h" + originalText);
    editor.onKeyPress(512 + 25);
    EXPECT_EQ(editor.getContent(), "h bc" + originalText);
    editor.onKeyPress(256 + 75);
    editor.onKeyPress(127);
    EXPECT_EQ(editor.getContent(), "h b" + originalText);
}