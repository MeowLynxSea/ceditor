#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include "container.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
class MyDeque : public Container<T> {
private:
    static const size_t CHUNK_SIZE = 8;  // 每个块的大小
    
    T** map;              // 中控器
    size_t map_capacity;  // 中控器容量
    size_t start_chunk;   // 起始块索引
    size_t start_pos;     // 起始块中的位置
    size_t size_;

    void initialize_map(size_t n) {
        map_capacity = std::max(size_t(8), n / CHUNK_SIZE + 1);
        map = new T*[map_capacity];
        for (size_t i = 0; i < map_capacity; i++) {
            map[i] = new T[CHUNK_SIZE];
        }
        start_chunk = map_capacity / 2;
        start_pos = CHUNK_SIZE / 2;
        size_ = 0;
    }

    void ensure_capacity(size_t needed_chunks) {
        if (needed_chunks > map_capacity) {
            size_t new_capacity = map_capacity * 2;
            T** new_map = new T*[new_capacity];

            size_t new_start = (new_capacity - needed_chunks) / 2;
            for (size_t i = 0; i < map_capacity; i++) {
                new_map[new_start + i] = map[i];
            }

            for (size_t i = 0; i < new_start; i++) {
                new_map[i] = new T[CHUNK_SIZE];
            }
            for (size_t i = new_start + map_capacity; i < new_capacity; i++) {
                new_map[i] = new T[CHUNK_SIZE];
            }
            
            delete[] map;
            map = new_map;
            start_chunk = new_start;
            map_capacity = new_capacity;
        } else if (needed_chunks < map_capacity / 4 && needed_chunks >= 0) {
            size_t new_capacity = map_capacity / 2;
            T** new_map = new T*[new_capacity];

            size_t new_start = (new_capacity - needed_chunks) / 2;
            for (size_t i = 0; i < needed_chunks; i++) {
                new_map[new_start + i] = map[start_chunk + i];
            }

            for(size_t i = 0; i < new_start; i++) {
                new_map[i] = new T[CHUNK_SIZE];
            }
            for (size_t i = new_start + needed_chunks; i < new_capacity; i++) {
                new_map[i] = new T[CHUNK_SIZE];
            }

            for(size_t i = 0; i < start_chunk; i++) {
                delete[] map[i];
            }
            for(size_t i = start_chunk + needed_chunks; i < map_capacity; i++) {
                delete[] map[i];
            }

            delete[] map;
            map = new_map;
            start_chunk = new_start;
            map_capacity = new_capacity;
        }
    }

public:
    MyDeque() {
        initialize_map(0);
    }
    
    ~MyDeque() {
        for (size_t i = 0; i < map_capacity; i++) {
            delete[] map[i];
        }
        delete[] map;
    }

    void push_back(const T& value) {
        size_t end_chunk = (start_chunk + (start_pos + size_) / CHUNK_SIZE);
        size_t end_pos = (start_pos + size_) % CHUNK_SIZE;
        
        if (end_chunk >= map_capacity) {
            ensure_capacity(end_chunk + 1);
        }
        
        map[end_chunk][end_pos] = value;
        size_++;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("back of empty deque");
        }
        size_t end_chunk = (start_chunk + (start_pos + size_ - 1) / CHUNK_SIZE);
        size_t end_pos = (start_pos + size_ - 1) % CHUNK_SIZE;
        return map[end_chunk][end_pos];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("back of empty deque");
        }
        size_t end_chunk = (start_chunk + (start_pos + size_ - 1) / CHUNK_SIZE);
        size_t end_pos = (start_pos + size_ - 1) % CHUNK_SIZE;
        return map[end_chunk][end_pos];
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back from empty deque");
        }
        size_--;
        if((start_pos + size_ ) / CHUNK_SIZE + 1< map_capacity / 4) {
           ensure_capacity((start_pos + size_) / CHUNK_SIZE + 1);
        }
    }

    void push_front(const T& value) {
        if (start_pos == 0) {
            if (start_chunk == 0) {
                ensure_capacity(map_capacity + 1);
            }
            start_chunk--;
            start_pos = CHUNK_SIZE;
        }
        start_pos--;
        map[start_chunk][start_pos] = value;
        size_++;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front of empty deque");
        }
        return map[start_chunk][start_pos];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("front of empty deque");
        }
        return map[start_chunk][start_pos];
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front from empty deque");
        }
        start_pos++;
        if (start_pos == CHUNK_SIZE) {
            start_chunk++;
            start_pos = 0;
        }
        size_--;
        if((start_pos + size_ ) / CHUNK_SIZE + 1< map_capacity / 4) {
           ensure_capacity((start_pos + size_) / CHUNK_SIZE + 1);
        }
    }

    T& operator[](size_t n) {
        size_t chunk = start_chunk + (start_pos + n) / CHUNK_SIZE;
        size_t pos = (start_pos + n) % CHUNK_SIZE;
        return map[chunk][pos];
    }

    void push(const T& value) override {
        push_front(value);
    }

    void pop() override {
        pop_front();
    }

    T& top() override {
        return front();
    }

    const T& top() const override {
        return front();
    }

    bool empty() const override {
        return size_ == 0;
    }

    size_t size() const override {
        return size_;
    }

    void clear() override {
        while(!empty()) pop();
    }
};

#endif