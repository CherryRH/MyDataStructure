#include <iostream>
#include <ctime>
#include "redBlackTree.h"

using namespace std;

int main() {
    srand(time(nullptr));

    RedBlackTree *tree = new RedBlackTree();

//    for (int i = 0; i < 10; i++) {
//        tree->insert(i);
//    }
//    tree->insert(3);
//    tree->insert(1);
//    tree->insert(5);
//    tree->insert(7);
//    tree->remove(7);
//    tree->insert(4);
//    tree->remove(1);
//    tree->printInOrder();

    const int numElements = 30000;
    int* elements = new int[numElements];

    // 插入测试
    for (int i = 0; i < numElements; ++i) {
        //cout << i << endl;
        int randomNumber = rand() % INT32_MAX + 1;
        while (true) {
            bool hasDouble = false;
            for (int j = 0; j < i; j++) {
                if (randomNumber == elements[j]) {
                    hasDouble = true;
                    break;
                }
            }
            if (hasDouble) {
                randomNumber = rand() % INT32_MAX + 1;
                continue;
            }
            else break;
        }
        elements[i] = randomNumber;
        tree->insert(randomNumber);
    }

    // 查找测试
    bool allFound = true;
    for (int i = 0; i < numElements; ++i) {
        if (elements[i] != 0) {
            if (!tree->find(elements[i])) {
                allFound = false;
                break;
            }
        }
    }
    if (allFound) {
        std::cout << "All elements found" << std::endl;
    } else {
        std::cout << "Some elements not found" << std::endl;
    }

    // 删除测试
    for (int i = 0; i < numElements / 10; i++) {
        int randomRemoveIndex = rand() % numElements;
        tree->remove(elements[randomRemoveIndex]);
        elements[randomRemoveIndex] = 0;
    }
    allFound = true;
    for (int i = 0; i < numElements; ++i) {
        if (elements[i] != 0) {
            if (!tree->find(elements[i])) {
                allFound = false;
                break;
            }
        }
        else if (elements[i] == 0) {
            if (tree->find(elements[i])) {
                allFound = false;
                break;
            }
        }
    }
    if (allFound) {
        std::cout << "All elements found" << std::endl;
    } else {
        std::cout << "Some elements not found" << std::endl;
    }

    // 释放内存
    delete tree;

    return 0;
}