#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cstdint>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <list>

namespace skiplist {
using key_type = uint64_t;

using value_type = std::string;

struct ListNode {
    key_type key;
    value_type value;
    std::vector<ListNode*> forward;

    ListNode(key_type k, const value_type& v, int level)
    : key(k), value(v), forward(level, nullptr) {}
};

class SkipList {
    ListNode *head;
    double probability;
    int MaxLevel;
    int level;
    int length;
    std::default_random_engine generator;

    //生成随机层数
    int random_level() {
        int l = 0;
        while (l < MaxLevel && std::bernoulli_distribution(probability)(generator)) {
            l++;
        }
        return l;
    }

public:
	explicit SkipList(double p = 0.5);

    ~SkipList();

    void reset();

    void clear(ListNode *x);

	void put(key_type key, const value_type &val);

    bool del(key_type key);

	std::string get(key_type key) const;

	int query_distance(key_type key) const;

    void scan(key_type key1, key_type key2, std::list<std::pair<key_type, value_type>> &list);

    int getLength();

};

}

#endif // SKIPLIST_H
