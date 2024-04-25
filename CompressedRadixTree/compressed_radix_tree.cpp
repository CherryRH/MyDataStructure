#include "compressed_radix_tree.hpp"

CompressedRadixTree::CompressedRadixTree()
{
    root = new Node();
}

CompressedRadixTree::~CompressedRadixTree()
{
    clear(root);
}

void CompressedRadixTree::clear(Node *x)
{
    for (int i = 0; i < x->children.size(); i++)
    {
        if (x->children[i])
        {
            clear(x->children[i]);
        }
    }
    delete x;
}

void CompressedRadixTree::insert(int32_t value)
{
    Node *tmp = root;
    // 遍历value的16个双bit
    int i = 30;
    while (i >= 0) {
        // 用第一个双bit确定子节点
        Node *it = nullptr;
        for (int j = 0; j < tmp->children.size(); j++) {
            if (tmp->children[j]->data[0] == ((value >> i) & 3)) {
                it = tmp->children[j];
                break;
            }
        }
        i -= 2;
        if (it) {
            // 子节点找到，继续比对直到不同，并且把后面的部分截断作为子节点
            tmp = it;
            int limit = tmp->data.size();
            for (int z = 1; z < limit; z++) {
                if (tmp->data[z] != ((value >> i) & 3)) {
                    Node *newChild = new Node();
                    // 截断父节点移到中间节点
                    newChild->data.insert(newChild->data.begin(), tmp->data.begin() + z, tmp->data.end());
                    tmp->data.erase(tmp->data.begin() + z, tmp->data.end());
                    // 中间节点关系设置
                    newChild->father = tmp;
                    newChild->children = tmp->children;
                    // 父节点关系设置
                    tmp->children.clear();
                    tmp->children.push_back(newChild);
                    // 子节点关系设置
                    for (int l = 0; l < newChild->children.size(); l++) {
                        newChild->children[l]->father = newChild;
                    }
                    break;
                }
                i -= 2;
            }
        }
        else {
            // 子节点没有找到，用剩余的bit创建新子节点
            std::vector<std::bitset<2>> rest;
            i += 2;
            while (i >= 0) {
                rest.push_back(((value >> i) & 3));
                i -= 2;
            }
            Node *newChild = new Node();
            newChild->data = rest;
            newChild->father = tmp;
            tmp->children.push_back(newChild);
        }
    }
}

void CompressedRadixTree::remove(int32_t value)
{
    Node *tmp = root;
    // 遍历value的16个双bit，找到最终的叶节点
    int i = 30;
    while (i >= 0) {
        // 用第一个双bit确定子节点
        Node *it = nullptr;
        for (int j = 0; j < tmp->children.size(); j++) {
            if (tmp->children[j]->data[0] == ((value >> i) & 3)) {
                it = tmp->children[j];
                break;
            }
        }
        i -= 2;
        if (it) {
            // 子节点找到，如果对比不同则返回
            tmp = it;
            int limit = tmp->data.size();
            for (int z = 1; z < limit; z++) {
                if (tmp->data[z] != ((value >> i) & 3)) return;
                i -= 2;
            }
        }
        else {
            // 子节点没有找到，直接返回
            return;
        }
    }
    // 删除叶节点
    Node *father = tmp->father;
    auto index = std::find(father->children.begin(), father->children.end(), tmp);
    delete tmp;
    father->children.erase(index);
    // 向上回溯，如果父节点只有一个子节点，则向上合并
    while (father != root) {
        if (father->children.size() == 1) {
            Node *it = father->children[0];
            // 合并子节点
            father->data.insert(father->data.end(), it->data.begin(), it->data.end());
            // 重新设置子节点
            father->children.insert(father->children.end(), it->children.begin(), it->children.end());
            delete it;
            father->children.erase(father->children.begin());
            for (int l = 0; l < father->children.size(); l++) {
                father->children[l]->father = father;
            }
        }
        else father = father->father;
    }
}

bool CompressedRadixTree::find(int32_t value)
{
    Node *tmp = root;
    // 遍历value的16个双bit
    int i = 30;
    while (i >= 0) {
        // 用第一个双bit确定子节点
        Node *it = nullptr;
        for (int j = 0; j < tmp->children.size(); j++) {
            if (tmp->children[j]->data[0] == ((value >> i) & 3)) {
                it = tmp->children[j];
                break;
            }
        }
        i -= 2;
        if (it) {
            // 子节点找到，如果对比bit不同则返回false
            tmp = it;
            int limit = tmp->data.size();
            for (int z = 1; z < limit; z++) {
                if (tmp->data[z] != ((value >> i) & 3)) return false;
                i -= 2;
            }
        }
        else {
            // 子节点没有找到，直接返回false
            return false;
        }
    }
    return true;
}

uint32_t CompressedRadixTree::size()
{
    uint32_t result = getSize(root);
    return result;
}

uint32_t CompressedRadixTree::getSize(Node *x)
{
    uint32_t result = 0;
    if (x) result++;
    else return 0;
    for (int i = 0; i < x->children.size(); i++)
    {
        if (x->children[i]) result += getSize(x->children[i]);
    }
    return result;
}

uint32_t CompressedRadixTree::height()
{
    uint32_t result = getHeight(root);
    return result;
}

uint32_t CompressedRadixTree::getHeight(Node *x)
{
    uint32_t result = 0;
    if (!x) return 0;
    for (int i = 0; i < x->children.size(); i++)
    {
        if (x->children[i]) {
            uint32_t tmp = getHeight(x->children[i]);
            result = tmp > result ? tmp : result;
        }
    }
    return result + 1;
}