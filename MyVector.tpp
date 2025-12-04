#pragma once

#include <utility>
#include <stdexcept>
#include <algorithm> // std::max

template<typename T>
MyVector<T>::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] m_data;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity)
{
    if (m_capacity > 0) {
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) return *this;

    delete[] m_data;
    m_data = nullptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    if (m_capacity > 0) {
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }

    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this == &other) return *this;

    delete[] m_data;

    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

    return *this;
}

template<typename T>
void MyVector<T>::grow() {
    // обеспечить реальное увеличение capacity (минимум +1)
    size_t increment = (m_capacity / 2);
    if (increment == 0) increment = 1; // для m_capacity == 0 или 1
    size_t newCapacity = m_capacity + increment;

    // на случай переполнения (маловероятно для учебных задач)
    if (newCapacity <= m_capacity) newCapacity = m_capacity + 1;

    T* newData = new T[newCapacity];

    for (size_t i = 0; i < m_size; ++i)
        newData[i] = std::move(m_data[i]);

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

template<typename T>
void MyVector<T>::push_back(const T& value) {
    if (m_size >= m_capacity) grow();
    m_data[m_size++] = value;
}

template<typename T>
void MyVector<T>::push_back(T&& value) {
    if (m_size >= m_capacity) grow();
    m_data[m_size++] = std::move(value);
}

template<typename T>
void MyVector<T>::insert(size_t index, const T& value) {
    if (index > m_size)
        throw std::out_of_range("Index out of range in insert()");

    if (m_size >= m_capacity) grow();

    // сдвиг вправо (включая возможность вставки в конец)
    for (size_t i = m_size; i > index; --i)
        m_data[i] = std::move(m_data[i - 1]);

    m_data[index] = value;
    ++m_size;
}

template<typename T>
void MyVector<T>::erase(size_t index) {
    if (index >= m_size)
        throw std::out_of_range("Index out of range in erase()");

    for (size_t i = index; i + 1 < m_size; ++i)
        m_data[i] = std::move(m_data[i + 1]);

    --m_size;
}

template<typename T>
void MyVector<T>::clear() {
    m_size = 0;
}
