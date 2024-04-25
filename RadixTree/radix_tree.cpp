#include "radix_tree.hpp"

RadixTree::RadixTree()
{
    root = new Node();
}

RadixTree::~RadixTree()
{
    clear(root);
}

void RadixTree::clear(Node *x)
{
    for (int i = 0; i < 4; i++)
    {
        if (x->children[i])
        {
            clear(x->children[i]);
        }
    }
    delete x;
}

void RadixTree::insert(int32_t value)
{
    Node *tmp = root;
    std::bitset<32> val = value;
    // 遍历value的16个双bit
    for (int i = 30; i >= 0; i -= 2) {
        // 取2位
        // 如果对应子节点为空，则创建
        int index = (value >> i) & 3;
        if (!tmp->children[index]) {
            tmp->children[index] = new Node(index);
            tmp->children[index]->father = tmp;
        }
        tmp = tmp->children[index];
    }
}

void RadixTree::remove(int32_t value)
{
    Node *tmp = root;
    // 遍历value的16个双bit，找到最终的叶节点
    for (int i = 30; i >= 0; i -= 2) {
        // 取2位
        // 如果对应子节点不存在，则直接返回
        int index = (value >> i) & 3;
        if (!tmp->children[index]) {
            return;
        }
        tmp = tmp->children[index];
    }
    // 删除叶节点
    Node *father = tmp->father;
    int index = tmp->data.to_ulong();
    delete father->children[index];
    father->children[index] = nullptr;
    // 向上回溯，如果父节点没有其他子节点，则删除父节点（根节点不删除）
    while (father != root) {
        if (father->isLeaf()) {
            index = father->data.to_ulong();
            father = father->father;
            delete father->children[index];
            father->children[index] = nullptr;
        }
        else father = father->father;
    }
}

bool RadixTree::find(int32_t value)
{
    Node *tmp = root;
    // 遍历value的16个双bit
    for (int i = 30; i >= 0; i -= 2) {
        // 取2位
        // 如果对应子节点不存在，则直接返回false
        int index = (value >> i) & 3;
        if (!tmp->children[index]) {
            return false;
        }
        tmp = tmp->children[index];
    }
    return true;
}

uint32_t RadixTree::size()
{
    uint32_t result = getSize(root);
    return result;
}

uint32_t RadixTree::getSize(Node *x)
{
    uint32_t result = 0;
    if (x) result++;
    else return 0;
    for (int i = 0; i < 4; i++)
    {
        if (x->children[i]) result += getSize(x->children[i]);
    }
    return result;
}

uint32_t RadixTree::height()
{
    uint32_t result = getHeight(root);
    return result;
}

uint32_t RadixTree::getHeight(Node *x)
{
    uint32_t result = 0;
    if (!x) return 0;
    for (int i = 0; i < 4; i++)
    {
        if (x->children[i]) {
            uint32_t tmp = getHeight(x->children[i]);
            result = tmp > result ? tmp : result;
        }
    }
    return result + 1;
}