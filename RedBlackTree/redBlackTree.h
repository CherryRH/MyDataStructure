#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK };

template <class T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node (const T& data = T(), Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, Color c = Color::RED)
        :data(data), left(l), right(r), parent(p), color(c) {}
};

// 空叶节点
template <class T>
Node<T>* NIL = new Node<T>(T(), nullptr, nullptr, nullptr, Color::BLACK);

template <class T>
class RedBlackTree {
private:
    Node<T>* root;

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() {}

    void insert(const T& data);
    void remove(const T& data);
    bool find(const T& data) const;
    void clear();
    void printInOrder() const;
};

#endif /* RED_BLACK_TREE_H */