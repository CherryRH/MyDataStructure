#include <iostream>
#include "redBlackTree.h"

RedBlackTree::RedBlackTree() : root(nullptr) {
    NIL = new Node(0, nullptr, nullptr, nullptr, Color::BLACK);
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::clear() {
    deleteTree(root);
    root = nullptr;
    NIL->parent = nullptr;
}

void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node *pt) {
    // 父节点
    Node* parent_pt = nullptr;
    // 祖父节点
    Node* grand_parent_pt = nullptr;

    while (pt != root && pt->color == RED && pt->parent->color == RED) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            // 叔父节点
            Node* uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                if (pt == parent_pt->left) {
                    parent_pt->color = BLACK;
                    grand_parent_pt->color = RED;
                    rotateRight(grand_parent_pt);
                } else {
                    pt->color = BLACK;
                    grand_parent_pt->color = RED;
                    rotateLeft(parent_pt);
                    rotateRight(grand_parent_pt);
                }
            }
        } else {
            Node* uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    parent_pt->color = BLACK;
                    grand_parent_pt->color = RED;
                    rotateLeft(grand_parent_pt);
                }
                else {
                    pt->color = BLACK;
                    grand_parent_pt->color = RED;
                    rotateRight(parent_pt);
                    rotateLeft(grand_parent_pt);
                }
            }
        }
    }
    root->color = BLACK;
}

Node* RedBlackTree::insertNode(Node* r, Node* pt) {
    if (r == nullptr) {
        return pt;
    }
    if (pt->data < r->data) {
        r->left = insertNode(r->left, pt);
        r->left->parent = r;
    }
    else if (pt->data > r->data) {
        r->right = insertNode(r->right, pt);
        r->right->parent = r;
    }
    return r;
}

void RedBlackTree::inorderUtil(Node* x) const {
    if (x == nullptr) return;
    inorderUtil(x->left);
    std::cout << x->data << "(" << ((x->color == BLACK) ? "BLACK" : "RED") << ")" << ((x == root) ? "(ROOT)" : "") << " ";
    inorderUtil(x->right);
}

void RedBlackTree::insert(const int &data) {
    // 如果已存在则不用插入
    if (find(data)) return;
    Node* new_node = new Node(data);
    root = insertNode(root, new_node);
    fixInsert(new_node);
}

void RedBlackTree::printInOrder() const {
    inorderUtil(root);
    std::cout << std::endl;
}

Node* RedBlackTree::getSuccessor(Node *pt) {
    if(pt->right != nullptr) {
        Node* tmp = pt->right;
        while(tmp->left != nullptr) tmp = tmp->left;
        return tmp;
    }
    Node* parent = pt->parent;
    while(parent != nullptr && pt == parent->right)
    {
        pt = parent;
        parent = pt->parent;
    }
    return parent;
}

void RedBlackTree::fixRemove(Node *pNode) {
    // 删除的节点
    Node* pDeleteNode = nullptr;
    // 删除节点的子节点
    Node* pCDeleteNode = nullptr;
    // 删除节点的父结点
    Node* p = nullptr;
    // 确定被删除的节点并与接替节点交换
    if (pNode->left == nullptr || pNode->right == nullptr) pDeleteNode = pNode;
    else pDeleteNode = getSuccessor(pNode);
    if (pDeleteNode != pNode) pNode->data = pDeleteNode->data;
    // 确定删除节点的子节点（可能为空）
    if (pDeleteNode->left) pCDeleteNode = pDeleteNode->left;
    else if (pDeleteNode->right) pCDeleteNode = pDeleteNode->right;
    // 删除节点（如果是根节点则需要调整root）
    if (pDeleteNode == root) {
        root = pCDeleteNode;
        if (pCDeleteNode) pCDeleteNode->parent = nullptr;
    }
    else {
        p = pDeleteNode->parent;
        if (pDeleteNode == p->left) p->left = pCDeleteNode;
        else if (pDeleteNode == p->right) p->right = pCDeleteNode;
        if (pCDeleteNode) pCDeleteNode->parent = p;
    }
    // 调整双黑现象
    if (pDeleteNode->color == BLACK) {
        // 如果删除节点的子节点为空，则临时增加一个空子节点
        if (!pCDeleteNode) {
            pNode = NIL;
            pNode->parent = p;
            if (p->left == nullptr) p->left = pNode;
            else if (p->right == nullptr) p->right = pNode;
        }
        else pNode = pCDeleteNode;
        while (pNode != root && pNode->color == BLACK) {
            if (pNode == pNode->parent->left) {
                //pNode的兄弟节点
                Node* pBNode = pNode->parent->right;
                // BB-3
                if (pBNode->color == RED) {
                    pBNode->color = BLACK;
                    pNode->parent->color = RED;
                    rotateLeft(pNode->parent);
                }
                else {
                    if ((pBNode->left == nullptr || pBNode->left->color == BLACK) && (pBNode->right == nullptr || pBNode->right->color == BLACK)) {
                        // BB-2-B
                        if (pBNode->parent->color == BLACK) {
                            pBNode->color = RED;
                            pNode = pNode->parent;
                        }
                        // BB-2-R
                        else {
                            pBNode->color = RED;
                            pBNode->parent->color = BLACK;
                            pNode = root;
                        }
                    }
                    // BB-1
                    else if (pBNode->right && pBNode->right->color == RED) {
                        pBNode->color = pNode->parent->color;
                        pNode->parent->color = BLACK;
                        pBNode->right->color = BLACK;
                        rotateLeft(pNode->parent);
                        pNode = root;
                    }
                    else if (pBNode->left && pBNode->left->color == RED) {
                        pBNode->left->color = pNode->parent->color;
                        pNode->parent->color = BLACK;
                        rotateRight(pBNode);
                        rotateLeft(pNode->parent);
                        pNode = root;
                    }
                }
            }
            else {
                //pNode的兄弟节点
                Node* pBNode = pNode->parent->left;
                // BB-3
                if (pBNode->color == RED) {
                    pBNode->color = BLACK;
                    pNode->parent->color = RED;
                    rotateRight(pNode->parent);
                }
                else {
                    if ((pBNode->left == nullptr || pBNode->left->color == BLACK) && (pBNode->right == nullptr || pBNode->right->color == BLACK)) {
                        // BB-2-B
                        if (pBNode->parent->color == BLACK) {
                            pBNode->color = RED;
                            pNode = pNode->parent;
                        }
                        // BB-2-R
                        else {
                            pBNode->color = RED;
                            pBNode->parent->color = BLACK;
                            pNode = root;
                        }
                    }
                    // BB-1
                    else if (pBNode->left && pBNode->left->color == RED) {
                        pBNode->color = pNode->parent->color;
                        pNode->parent->color = BLACK;
                        pBNode->left->color = BLACK;
                        rotateRight(pNode->parent);
                        pNode = root;
                    }
                    else if (pBNode->right && pBNode->right->color == RED) {
                        pBNode->right->color = pNode->parent->color;
                        pNode->parent->color = BLACK;
                        rotateLeft(pBNode);
                        rotateRight(pNode->parent);
                        pNode = root;
                    }
                }
            }
        }
        // 断开临时空节点
        if (p->left == NIL) p->left = nullptr;
        else if (p->right == NIL) p->right = nullptr;
        NIL->parent = nullptr;
    }
    // 如果删除节点的子节点为红，改为黑色即可恢复
    if (pCDeleteNode) pCDeleteNode->color = BLACK;
    // 删除节点
    delete pDeleteNode;
}

bool RedBlackTree::find(const int &data) const{
    Node* tmp = root;
    while(tmp != nullptr) {
        if(data < tmp->data) tmp = tmp->left;
        else if(data > tmp->data) tmp = tmp->right;
        else return true;
    }
    return false;
}

void RedBlackTree::remove(const int &data) {
    Node* pNode = root;
    // 找到目标的节点
    while(pNode != nullptr) {
        if(data < pNode->data) pNode = pNode->left;
        else if(data > pNode->data) pNode = pNode->right;
        else break;
    }
    if (pNode == nullptr) return;
    fixRemove(pNode);
}

void RedBlackTree::deleteTree(Node* x) {
    if (x == nullptr) return;
    deleteTree(x->left);
    deleteTree(x->right);
    delete x;
}