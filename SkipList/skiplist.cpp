#include "skiplist.h"
#include <random>
#include <chrono>
#include <optional>

namespace skiplist {

SkipList::SkipList(double p)
:probability(p), MaxLevel(32),generator(std::chrono::system_clock::now().time_since_epoch().count()){
    head = new ListNode(0, "", MaxLevel);
    level = 0;
    length = 0;
}

SkipList::~SkipList() {
    clear(head);
}

void SkipList::reset() {
    clear(head);
    level = 0;
    length = 0;
    head = new ListNode(0, "", MaxLevel);
}

void SkipList::clear(ListNode *x) {
    if (x->forward[0] != nullptr) {
        clear(x->forward[0]);
    }
    delete x;
}

void SkipList::put(key_type key, const value_type &val) {
    //开始指向头结点
    ListNode* x = head;
    //每层需要插入的前一个结点
    ListNode* update[MaxLevel];
    //比较key值找到update结点
    for (int i = level; i >= 0; --i) {
        while (x->forward[i] != nullptr && x->forward[i]->key <= key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = update[0];
    if(x != nullptr && x->key == key) {
        x->value = val;
    }
    else {
        int new_level = random_level();
        if (new_level > level) {
            if(new_level >= MaxLevel) new_level = MaxLevel - 1;
            for (int i = level + 1; i <= new_level; i++) {
                update[i] = head;
            }
            level = new_level;
        }
        x = new ListNode(key, val, new_level + 1);
        for (int i = 0; i <= new_level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
        length++;
    }
}

std::string SkipList::get(key_type key) const {
    //if key == 0
    if (key == 0) {
        if (head->value == "" || head->value == "~DELETE~") {
            return "";
        }
        else return head->value;
    }
    ListNode* x = head;
    for (int i = level; i >= 0; --i) {
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != nullptr && x->key == key) {
        if (x->value == "" || x->value == "~DELETE~") {
            return "";
        }
        else return x->value;
    } else {
        return "";
    }
}

bool SkipList::del(key_type key) {
    //if key == 0
    if (key == 0) {
        if(head->value == "" || head->value == "~DELETE~") {
            return false;
        }
        else {
            head->value = "~DELETE~";
            return true;
        }
    }
    //如果跳表为空
    if (length == 0) return false;
    //如果没有找到
    if (get(key) == "") return false;
    for (int i = level; i >= 0; --i) {
        ListNode* x = head;
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        ListNode* pre = x;
        x = x->forward[i];
        if (x->key == key) {
            pre->forward[i] = x->forward[i];
            if (i == 0) {
                delete x;
            }
        }
    }
    //检查高度有没有降低
    for (int i = level; i > 0; --i) {
        if (head->forward[i] == nullptr) level--;
        else break;
    }
    return true;
}

int SkipList::query_distance(key_type key) const {
    //if key == 0
    if(key == 0) {
        return 0;
    }
    ListNode* x = head;
    int distance = 1;
    for (int i = level; i >= 0; --i) {
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
            distance++;
        }
    }
    return distance;
}

void SkipList::scan(key_type key1, key_type key2, std::list<std::pair<key_type, value_type>> &list) {
    ListNode* begin = head;
    //if key contains 0
    if(key1 == 0 && head->value != "" && head->value != "~DELETE~") {
        list.push_back(std::make_pair(0, head->value));
    }
    for (int i = level; i >= 0; --i) {
        while (begin->forward[i] != nullptr && begin->forward[i]->key < key1) {
            begin = begin->forward[i];
        }
    }
    while (begin->forward[0] != nullptr && begin->forward[0]->key <= key2) {
        begin = begin->forward[0];
        if(begin->value == "" || begin->value == "~DELETE~") continue;
        list.push_back(std::make_pair(begin->key, begin->value));
    }
}

//get the number of key-values
int SkipList::getLength() {
    if(head->value != "") {
        return length + 1;
    }
    return length;
}

} // namespace skiplist
