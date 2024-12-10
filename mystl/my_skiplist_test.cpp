#include "my_skiplist.h"
#include <cassert>

int main() {
    // 测试默认构造函数
    SkipList<int, std::string> skipList;
    
    // 测试 insert 和 find
    skipList.insert(1, "one");
    std::string value;
    assert(skipList.find(1, value) && value == "one");

    // 测试 erase
    assert(skipList.erase(1));
    assert(!skipList.find(1, value));

    // 测试多个插入和查找
    skipList.insert(2, "two");
    skipList.insert(3, "three");
    skipList.insert(4, "four");
    assert(skipList.find(2, value) && value == "two");
    assert(skipList.find(3, value) && value == "three");
    assert(skipList.find(4, value) && value == "four");

    // 测试 erase
    assert(skipList.erase(3));
    assert(!skipList.find(3, value));

    // 测试 display (不进行断言，只是输出当前跳表结构)
    // skipList.display();

    return 0;
}
