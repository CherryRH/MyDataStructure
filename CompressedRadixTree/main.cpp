//
// Created by 陈瑞涵 on 24-4-25.
//
#include <iostream>
#include "compressed_radix_tree.hpp"

using namespace std;

int main() {
    CompressedRadixTree tree;
    for (int i = 0; i < 10000; i++) {
        tree.insert(i);
    }
    for (int i = 0; i < 10000; i++) {
        if (!tree.find(i)) {
            cout << "Not found." << endl;
            return 0;
        }
    }
    cout << "OK" << endl;
    return 0;
}