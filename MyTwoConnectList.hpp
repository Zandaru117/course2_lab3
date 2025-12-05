#pragma once
#include <memory>
#include <cstddef>
#include <utility>

template<typename T>
class TwoConnectlist {
    struct Node {
        T data_;
        Node* prev_;
        std::unique_ptr<Node> next_;
        Node(const T& v) : data_(v), prev_(nullptr), next_(nullptr) {}
        Node(T&& v) : data_(std::move(v)), prev_(nullptr), next_(nullptr) {}
    };
    std::unique_ptr<Node> head_;
    Node* tail_;
    size_t size_;

public:
    TwoConnectlist();
    TwoConnectlist(const TwoConnectlist& other);
    TwoConnectlist(TwoConnectlist&& other) noexcept;
    TwoConnectlist& operator=(TwoConnectlist&& other) noexcept;
    ~TwoConnectlist();

    void push_back(const T& value);
    void push_back(T&& value);
    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);
    void erase(size_t index);
    size_t size() const;
    T& operator[](size_t index);

    class iterator {
        Node* node_;

    public:
        iterator(Node* n) : node_(n) {}
        T& operator*() { return node_->data_; }
        iterator& operator++() { node_ = node_->next_.get(); return *this; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }
    };

    iterator begin() { return iterator(head_.get()); }
    iterator end() { return iterator(nullptr); }

private:
    Node* get_node(size_t index);
};

#include "MyTwoConnectList.tpp"