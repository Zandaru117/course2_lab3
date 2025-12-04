#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector {
public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    void push_back(const T& value);
    void push_back(T&& value);
    void insert(size_t index, const T& value);
    void erase(size_t index);

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; } // для отладки
    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }
    void clear();

    class Iterator {
    public:
        Iterator(T* ptr) : m_ptr(ptr) {}
        T& operator*() { return *m_ptr; }
        Iterator& operator++() { ++m_ptr; return *this; }
        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }
    private:
        T* m_ptr;
    };

    Iterator begin() { return Iterator(m_data); }
    Iterator end()   { return Iterator(m_data ? m_data + m_size : m_data); }

private:
    void grow();

    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

#include "MyVector.tpp"
