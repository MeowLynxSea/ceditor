#include <iostream>
#include <random>
#include "my_vector.h"
#include <limits>

template<typename K, typename V>
class SkipList {
private:
    struct Node {
        K key;
        V value;
        std::vector<Node*> forward; // 存储每一层的前向指针

        Node(K k, V v, int level)
            : key(k), value(v), forward(level, nullptr) {}
    };

    Node* head;     // 头节点
    int maxLevel;   // 最大层数
    int currentLevel; // 当前层数
    float probability; // 生成上层节点的概率

    // 生成随机层数
    int randomLevel() {
        int level = 1;
        while ((float)rand()/RAND_MAX < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLvl = 16, float p = 0.5)
        : maxLevel(maxLvl), probability(p), currentLevel(1) {
        K minKey = std::numeric_limits<K>::min();
        head = new Node(minKey, V(), maxLevel);
    }

    void insert(K key, V value) {
        MyVector<Node*> update(maxLevel, nullptr);
        Node* current = head;

        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr &&
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && current->key == key) {
            current->value = value;
            return;
        }

        int newLevel = randomLevel();

        if (newLevel > currentLevel) {
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = head;
            }
            currentLevel = newLevel;
        }

        Node* newNode = new Node(key, value, newLevel);

        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool find(K key, V& value) {
        Node* current = head;

        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr &&
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];

        if (current != nullptr && current->key == key) {
            value = current->value;
            return true;
        }
        return false;
    }

    bool erase(K key) {
        MyVector<Node*> update(maxLevel, nullptr);
        Node* current = head;

        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr &&
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->key != key) {
            return false;
        }

        for (int i = 0; i < currentLevel; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        delete current;

        while (currentLevel > 1 && head->forward[currentLevel - 1] == nullptr) {
            currentLevel--;
        }

        return true;
    }

    size_t size() {
        size_t count = 0;
        Node* current = head->forward[0];
        while (current != nullptr) {
            count++;
            current = current->forward[0];
        }
        return count;
    }

    bool empty() {
        return head->forward[0] == nullptr;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        head = new Node(std::numeric_limits<K>::min(), V(), maxLevel);
        currentLevel = 1;
    }

    void display() {
        for (int i = currentLevel - 1; i >= 0; i--) {
            Node* current = head->forward[i];
            std::cout << "Level " << i << ": ";
            while (current != nullptr) {
                std::cout << current->key << ":" << current->value << " ";
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }

    ~SkipList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
};