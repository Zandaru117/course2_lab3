#pragma once
#include <utility>

template<typename T>
MyTwoConnectList<T>::MyTwoConnectList() : head(nullptr), tail(nullptr), m_size(0) {}

template<typename T>
MyTwoConnectList<T>::~MyTwoConnectList() { clear(); }

template<typename T>
void MyTwoConnectList<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    m_size = 0;
}

template<typename T>
MyTwoConnectList<T>::MyTwoConnectList(const MyTwoConnectList& other)
    : head(nullptr), tail(nullptr), m_size(0) {
    Node* curr = other.head;
    while (curr) {
        push_back(curr->value);
        curr = curr->next;
    }
}

template<typename T>
MyTwoConnectList<T>::MyTwoConnectList(MyTwoConnectList&& other) noexcept
    : head(other.head), tail(other.tail), m_size(other.m_size) {
    other.head = other.tail = nullptr;
    other.m_size = 0;
}

template<typename T>
MyTwoConnectList<T>& MyTwoConnectList<T>::operator=(const MyTwoConnectList& other) {
    if (this == &other) return *this;
    clear();
    Node* curr = other.head;
    while (curr) {
        push_back(curr->value);
        curr = curr->next;
    }
    return *this;
}

template<typename T>
MyTwoConnectList<T>& MyTwoConnectList<T>::operator=(MyTwoConnectList&& other) noexcept {
    if (this == &other) return *this;
    clear();
    head = other.head;
    tail = other.tail;
    m_size = other.m_size;
    other.head = nullptr;
    other.tail = nullptr;
    other.m_size = 0;
    return *this;
}

template<typename T>
void MyTwoConnectList<T>::push_back(const T& value) {
    Node* n = new Node(value);
    if (!head) {
        head = tail = n;
    } else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
    m_size++;
}

template<typename T>
void MyTwoConnectList<T>::insert(size_t index, const T& value) {
    if (index == 0) {
        Node* n = new Node(value);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
    } else if (index == m_size) {
        push_back(value);
        return;
    } else {
        Node* curr = head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        Node* n = new Node(value);
        n->prev = curr->prev;
        n->next = curr;

        curr->prev->next = n;
        curr->prev = n;
    }
    m_size++;
}

template<typename T>
void MyTwoConnectList<T>::erase(size_t index) {
    Node* curr = head;
    for (size_t i = 0; i < index; i++)
        curr = curr->next;

    if (curr->prev) curr->prev->next = curr->next;
    else head = curr->next;

    if (curr->next) curr->next->prev = curr->prev;
    else tail = curr->prev;

    delete curr;
    m_size--;
}

template<typename T>
T& MyTwoConnectList<T>::operator[](size_t index) {
    Node* curr = head;
    for (size_t i = 0; i < index; i++)
        curr = curr->next;
    return curr->value;
}
