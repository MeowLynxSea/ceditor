#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;
using namespace testing;
using namespace std;

#include "utils/utils.h"

/*
std::string fileExt = fileName.substr(fileName.find_last_of(".") + 1);
    if(fileExt == "txt") {
        return "plaintext";
    } else if(fileExt == "html") {
        return "html";
    } else if(fileExt == "css") {
        return "css";
    } else if(fileExt == "js") {
        return "js";
    } else if(fileExt == "json") {
        return "json";
    } else if(fileExt == "xml") {
        return "xml";
    } else if(fileExt == "md") {
        return "markdown";
    } else if(fileExt == "py") {
        return "python";
    } else if(fileExt == "c") {
        return "c";
    } else if(fileExt == "cpp" || fileExt == "h" || fileExt == "hpp" || fileExt == "cc" || fileExt == "hh" || fileExt == "cxx" || fileExt == "hxx") {
        return "cpp";
    } else if(fileExt == "java") {
        return "java";
    } else if(fileExt == "cs") {
        return "csharp";
    } else if(fileExt == "go") {
        return "go";
    } else if(fileExt == "rs") {
        return "rust";
    } else if(fileExt == "php") {
        return "php";
    } else {
        return "plaintext"; // too much else if statements
    }
*/

TEST(Utils, getRuleByFileName) {
    EXPECT_EQ(getRuleByFileName("test/test_utils.cpp"), "cpp");
    EXPECT_EQ(getRuleByFileName("test/test_utils.h"), "cpp");
    EXPECT_EQ(getRuleByFileName("test/test_utils.py"), "python");
    EXPECT_EQ(getRuleByFileName("test/test_utils.txt"), "plaintext");
    EXPECT_EQ(getRuleByFileName("test/test_utils.html"), "html");
    EXPECT_EQ(getRuleByFileName("test/test_utils.css"), "css");
    EXPECT_EQ(getRuleByFileName("test/test_utils.js"), "js");
    EXPECT_EQ(getRuleByFileName("test/test_utils.json"), "json");
    EXPECT_EQ(getRuleByFileName("test/test_utils.xml"), "xml");
    EXPECT_EQ(getRuleByFileName("test/test_utils.md"), "markdown");
    EXPECT_EQ(getRuleByFileName("test/test_utils.java"), "java");
    EXPECT_EQ(getRuleByFileName("test/test_utils.cs"), "csharp");
    EXPECT_EQ(getRuleByFileName("test/test_utils.go"), "go");
    EXPECT_EQ(getRuleByFileName("test/test_utils.rs"), "rust");
    EXPECT_EQ(getRuleByFileName("test/test_utils.php"), "php");
    EXPECT_EQ(getRuleByFileName("test/test_utils"), "plaintext");
    EXPECT_EQ(getRuleByFileName("test/test_utils."), "plaintext");
    EXPECT_EQ(getRuleByFileName("test/test_utils.."), "plaintext");
}