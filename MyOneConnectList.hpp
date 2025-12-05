#pragma once

#include <cstddef>

template<typename T>
class MyOneConnectList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head;
    size_t m_size;

public:
    MyOneConnectList();
    ~MyOneConnectList();

    MyOneConnectList(const MyOneConnectList& other);
    MyOneConnectList(MyOneConnectList&& other) noexcept;
    MyOneConnectList& operator=(const MyOneConnectList& other);
    MyOneConnectList& operator=(MyOneConnectList&& other) noexcept;

    void push_back(const T& value);
    void insert(size_t index, const T& value);
    void erase(size_t index);

    T& operator[](size_t index);
    size_t size() const { return m_size; }

    class Iterator {
        Node* curr;
    public:
        Iterator(Node* c) : curr(c) {}
        T& operator*() { return curr->value; }
        Iterator& operator++() { curr = curr->next; return *this; }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end()   { return Iterator(nullptr); }
};

#include "MyOneConnectList.tpp"
