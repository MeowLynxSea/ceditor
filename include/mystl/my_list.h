#ifndef MY_LIST_H
#define MY_LIST_H

#include "container.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
class MyList : public Container<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {}
    };

    Node* head; // 指向链表头部
    Node* tail; // 指向链表尾部
    size_t size_;

public:
    MyList() : head(nullptr), tail(nullptr), size_(0) {}

    ~MyList() override {
        clear();
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size_++;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value, nullptr, head);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            head = new_node;
        }
        size_++;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop from empty list");
        }
        Node* to_delete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete to_delete;
        size_--;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front from empty list");
        }
        Node* to_delete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete to_delete;
        size_--;
    }

    void insert(size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("index out of range");
        }
        if (index == 0) {
            push_front(value);
        } else if (index == size_) {
            push_back(value);
        } else {
            Node* new_node = new Node(value);
            Node* current = head;
            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }
            new_node->prev = current;
            new_node->next = current->next;
            current->next->prev = new_node;
            current->next = new_node;
            size_++;
        }
    }

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        if (index == 0) {
            pop_front();
        } else if (index == size_ - 1) {
            pop_back();
        } else {
            Node* to_delete = head;
            for (size_t i = 0; i < index; i++) {
                to_delete = to_delete->next;
            }
            to_delete->prev->next = to_delete->next;
            if (to_delete->next) {
                to_delete->next->prev = to_delete->prev;
            }
            delete to_delete;
            size_--;
        }
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("top of empty list");
        }
        return tail->data;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("top of empty list");
        }
        return tail->data;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front of empty list");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("front of empty list");
        }
        return head->data;
    }

    class iterator {
    private:
        Node* node;

    public:
        iterator(Node* n = nullptr) : node(n) {}

        iterator& operator++() { // 前缀++
            if (node) node = node->next;
            return *this;
        }

        iterator operator++(int) { // 后缀++
            iterator iterator = *this;
            ++(*this);
            return iterator;
        }

        iterator& operator--() { // 前缀--
            if (node) node = node->prev;
            return *this;
        }

        iterator operator--(int) { // 后缀--
            iterator iterator = *this;
            --(*this);
            return iterator;
        }

        bool operator==(const iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const iterator& other) const {
            return node != other.node;
        }

        T& operator*() {
            return node->data;
        }

        const T& operator*() const {
            return node->data;
        }

        T* operator->() {
            return &(node->data);
        }

        const T* operator->() const {
            return &(node->data);
        }

        Node * get_node() const {
            return node;
        }
    };

    // 提供begin和end方法来返回迭代器
    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    iterator rbegin() const {
        return iterator(tail);
    }

    iterator rend() const {
        return iterator(nullptr);
    }

    void erase(iterator ite) {
        if (ite.get_node() == nullptr) {
            throw std::out_of_range("index out of range");
        }
        Node* to_delete = ite.get_node();
        if(to_delete->prev) {
            to_delete->prev->next = to_delete->next;
        } else {
            head = to_delete->next;
        }
        if(to_delete->next) {
            to_delete->next->prev = to_delete->prev;
        } else {
            tail = to_delete->prev;
        }
        delete to_delete;
        size_--;
    }

    void push(const T& value) override {
        push_back(value);
    }

    void pop() override {
        pop_back();
    }

    T& top() override {
        return back();
    }

    const T& top() const override {
        return back();
    }

    bool empty() const override {
        return size_ == 0;
    }

    size_t size() const override {
        return size_;
    }

    void clear() override {
        while(!empty()) {
            pop_back();
        }
    }
};

#endif
