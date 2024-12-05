#include "my_deque.h"
#include <cassert>

int main() {
    // 测试默认构造函数
    MyDeque<int> dq;
    assert(dq.empty());
    assert(dq.size() == 0);

    // 测试 push_back 和 back
    dq.push_back(1);
    assert(dq.back() == 1);
    assert(dq.size() == 1);

    // 测试 push_front 和 front
    dq.push_front(2);
    assert(dq.front() == 2);
    assert(dq.size() == 2);

    // 测试 pop_back
    dq.pop_back();
    assert(dq.front() == 2);
    assert(dq.size() == 1);

    // 测试 pop_front
    dq.pop_front();
    assert(dq.empty());
    assert(dq.size() == 0);

    // 测试 operator[]
    dq.push_back(3);
    dq.push_back(4);
    assert(dq[0] == 3);
    assert(dq[1] == 4);

    // 测试 clear
    dq.clear();
    assert(dq.empty());
    assert(dq.size() == 0);

    printf("All tests passed!\n");
    return 0;
}
