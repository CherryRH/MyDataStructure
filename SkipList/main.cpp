//
// Created by 陈瑞涵 on 24-4-25.
//
#include <iostream>
#include "skiplist.h"

using namespace std;

int main() {
    skiplist::SkipList skipList;
    for (int i = 0; i < 100; i++) {
        skipList.put(i, "a");
    }
    for (int i = 0; i < 100; i++) {
        if (skipList.get(i) != "a") {
            cout << "Not found." << endl;
            return 0;
        }
    }
    cout << "OK" << endl;
    return 0;
}