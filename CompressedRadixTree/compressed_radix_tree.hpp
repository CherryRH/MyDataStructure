// implement a radix tree that support node compressino and store int32_t values
// each parent node has 4 children, representing 2 bits
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
class CompressedRadixTree
{
    // 基数树节点
    struct Node
    {
        // 一个节点储存2 * n位二进制数
        std::vector<std::bitset<2>> data;
        // 最多4个子节点
        std::vector<Node*> children;
        // 父节点
        Node *father;

        Node() {
            father = nullptr;
        }
    };
    // 根节点
    Node *root;
public:
    CompressedRadixTree();
    ~CompressedRadixTree();
    void clear(Node *x);
    // basic operation
    void insert(int32_t value);
    void remove(int32_t value);
    bool find(int32_t value);
    // statistics
    uint32_t size();
    uint32_t getSize(Node *x);
    uint32_t height();
    uint32_t getHeight(Node *x);
};