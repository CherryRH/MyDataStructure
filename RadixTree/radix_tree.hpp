#include <cstdint>
#include <iostream>
#include <bitset>
class RadixTree
{
private:
    // 基数树节点
    struct Node
    {
        // 一个节点储存2位二进制数
        std::bitset<2> data;
        // 最多4个子节点
        Node* children[4];
        // 父节点
        Node *father;

        Node(int val = 0) {
            data = val;
            for (int i = 0; i < 4; i++) {
                children[i] = nullptr;
            }
            father = nullptr;
        }

        bool isLeaf() {
            for (int i = 0; i < 4; i++) {
                if (children[i])
                {
                    return false;
                }
            }
            return true;
        }
    };
    // 根节点
    Node *root;
public:
    RadixTree();
    ~RadixTree();
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
