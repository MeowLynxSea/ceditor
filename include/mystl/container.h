#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstddef>

template <typename T>
class Container {
public:
    virtual ~Container() = default;

    // 添加元素
    virtual void push(const T& value) = 0;

    // 移除元素
    virtual void pop() = 0;

    // 访问顶部元素
    virtual T& top() = 0;
    virtual const T& top() const = 0;

    // 检查容器是否为空
    virtual bool empty() const = 0;

    // 返回容器中的元素数量
    virtual size_t size() const = 0;

    // 清空容器
    virtual void clear() = 0;
};

#endif // CONTAINER_H
