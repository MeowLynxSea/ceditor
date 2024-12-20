#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "utils/SyntaxHighlighter.h"

std::string originalText = "#include <iostream>\n\
using namespace std;\n\
\
int main() {\n\
    cout << \"Hello, world!\"\n\
    return 0;\n\
}";

TEST(SyntaxHighlighter, test) {
    SyntaxHighlighter highlighter("cpp");
    RichText rst;
    rst = highlighter.highlight(originalText);
    EXPECT_EQ(rst.size(), 34);
    EXPECT_EQ(rst.getParts()[28].text, "return");
    EXPECT_EQ(rst.getParts()[21].text, "\n    ");
    EXPECT_EQ(rst.getParts()[26].text, "\"Hello, world!\"");
    EXPECT_EQ(rst.getParts()[16].text, "main");
}