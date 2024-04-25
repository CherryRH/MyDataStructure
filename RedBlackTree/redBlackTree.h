#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node (const int& data = 0, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, Color c = RED)
        :data(data), left(l), right(r), parent(p), color(c) {}
};

class RedBlackTree {
private:
    // 根节点
    Node* root;
    // 空节点（作临时子节点用）
    Node* NIL;
    // 左旋
    void rotateLeft(Node* x);
    // 右旋
    void rotateRight(Node* x);
    // 处理插入时双红现象
    void fixInsert(Node* pt);
    // 处理删除时双黑现象
    void fixRemove(Node* pNode);
    // 插入节点
    Node* insertNode(Node* r, Node* x);
    // 中序遍历
    void inorderUtil(Node* x) const;
    // 删除树
    void deleteTree(Node* x);
    // 获取后继节点
    Node* getSuccessor(Node *pt);
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(const int &data);
    void remove(const int &data);
    bool find(const int &data) const;
    void clear();
    void printInOrder() const;
};

#endif /* RED_BLACK_TREE_H */