#include "my_vector.h"
#include <cassert>

int main() {
    // 测试默认构造函数
    MyVector<int> vec1;
    assert(vec1.size() == 0);
    assert(vec1.capacity() == 0);

    // 测试带参数的构造函数
    MyVector<int> vec2(5, 2);
    assert(vec2.size() == 5);
    assert(vec2.capacity() == 5);
    for (size_t i = 0; i < vec2.size(); ++i) {
        assert(vec2[i] == 2);
    }

    // 测试 push_back 和 size
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    assert(vec1.size() == 3);

    // 测试 pop_back 和 size
    vec1.pop_back();
    assert(vec1.size() == 2);

    // 测试 back
    assert(vec1.back() == 2);

    // 测试 clear
    vec1.clear();
    assert(vec1.size() == 0);

    // 测试 reserve
    vec1.reserve(10);
    assert(vec1.capacity() == 10);

    // 测试 resize
    vec1.resize(5, 3);
    assert(vec1.size() == 5);
    for (size_t i = 0; i < vec1.size(); ++i) {
        assert(vec1[i] == 3);
    }

    // 测试 operator[]
    vec1[0] = 4;
    assert(vec1[0] == 4);

    // 测试 at
    assert(vec1.at(0) == 4);

    // 测试 copy assignment
    MyVector<int> vec3 = vec1;
    assert(vec3.size() == vec1.size());
    for (size_t i = 0; i < vec3.size(); ++i) {
        assert(vec3[i] == vec1[i]);
    }

    // 测试 move assignment
    MyVector<int> vec4 = std::move(vec3);
    assert(vec4.size() == 5);
    assert(vec3.size() == 0);

    return 0;
}
