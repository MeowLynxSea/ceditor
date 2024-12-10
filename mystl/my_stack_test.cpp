#include "my_stack.h"
#include <cassert>

int main() {
    // 测试默认构造函数
    MyStack<int> stack;
    assert(stack.empty());
    assert(stack.size() == 0);

    // 测试 push 和 top
    stack.push(1);
    assert(stack.top() == 1);
    assert(stack.size() == 1);

    // 测试 push 和 pop
    stack.push(2);
    stack.pop();
    assert(stack.top() == 1);
    assert(stack.size() == 1);

    // 测试 clear
    stack.clear();
    assert(stack.empty());
    assert(stack.size() == 0);

    // 测试多个 push 和 pop
    stack.push(3);
    stack.push(4);
    stack.push(5);
    assert(stack.top() == 5);
    stack.pop();
    assert(stack.top() == 4);
    stack.pop();
    assert(stack.top() == 3);
    assert(stack.size() == 1);

    return 0;
}
