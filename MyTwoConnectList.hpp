#pragma once

#include <cstddef>

template<template T>
class MyTwoConnectList
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;
        Node(const T& v) : value(v), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail:
    size_t m_size;
    
public:
    MyTwoConnectList();
    ~MyTwoConnectList();

    MyTwoConnectList(const MyTwoConnectList& other);
    MyTwoConnectList(MyTwoConnectList&& other) noexcept;
    MyTwoConnectList& operator=(const MyTwoConnectList& other);
    MyTwoConnectList& operator=(MyTwoConnectList&& other) noexcept;

    void push_back(const T& value);
    void insert(size_t index, const T& value);
    void erase(size_t index);

    class Iterator
    {
        Node* curr;
    public:
        Iterator(node* c) : curr(c) {}
        T& operator*() { return curr-> value; }
        Iterator& operator++() { curr = curr->next; return *this; }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end()   { return Iterator(nullptr); }
    
};

//#include "MyTwoConnectList.tpp"
