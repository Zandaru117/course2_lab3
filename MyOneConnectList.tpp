#pragma once

#include <utility>

template<typename T>
MyOneConnectList<T>::MyOneConnectList() : head(nullptr), m_size(0) {}

template<typename T>
MyOneConnectList<T>::~MyOneConnectList() {
    // ручная очистка вместо clear()
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
MyOneConnectList<T>::MyOneConnectList(const MyOneConnectList& other)
    : head(nullptr), m_size(0) 
{
    Node* curr = other.head;
    while (curr) {
        push_back(curr->value);
        curr = curr->next;
    }
}

template<typename T>
MyOneConnectList<T>::MyOneConnectList(MyOneConnectList&& other) noexcept
    : head(other.head), m_size(other.m_size) 
{
    other.head = nullptr;
    other.m_size = 0;
}

template<typename T>
MyOneConnectList<T>& MyOneConnectList<T>::operator=(const MyOneConnectList& other) {
    if (this == &other) return *this;

    // ручная очистка вместо clear()
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    m_size = 0;

    // копирование
    Node* curr = other.head;
    while (curr) {
        push_back(curr->value);
        curr = curr->next;
    }

    return *this;
}

template<typename T>
MyOneConnectList<T>& MyOneConnectList<T>::operator=(MyOneConnectList&& other) noexcept {
    if (this == &other) return *this;

    // ручная очистка вместо clear()
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    m_size = 0;

    // перенос
    head = other.head;
    m_size = other.m_size;

    other.head = nullptr;
    other.m_size = 0;

    return *this;
}

template<typename T>
void MyOneConnectList<T>::push_back(const T& value) {
    Node* n = new Node(value);
    if (!head) {
        head = n;
    } else {
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = n;
    }
    m_size++;
}

template<typename T>
void MyOneConnectList<T>::insert(size_t index, const T& value) {
    if (index == 0) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
    } else {
        Node* curr = head;
        for (size_t i = 0; i < index - 1; i++)
            curr = curr->next;
        Node* n = new Node(value);
        n->next = curr->next;
        curr->next = n;
    }
    m_size++;
}

template<typename T>
void MyOneConnectList<T>::erase(size_t index) {
    if (index == 0) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    } else {
        Node* curr = head;
        for (size_t i = 0; i < index - 1; i++)
            curr = curr->next;
        Node* tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
    }
    m_size--;
}

template<typename T>
T& MyOneConnectList<T>::operator[](size_t index) {
    Node* curr = head;
    for (size_t i = 0; i < index; i++)
        curr = curr->next;
    return curr->value;
}
