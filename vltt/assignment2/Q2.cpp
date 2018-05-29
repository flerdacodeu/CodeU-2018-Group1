#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

struct node {
    node *ancestor = nullptr;
    node *left = nullptr;
    node *right = nullptr;
    int value;
};

int up(node *first, node*second, const int pow) {
    int cnt = 0;
    while (first != nullptr && cnt != pow) {
        first = first->ancestor;
        cnt++;
    }
    cnt = 0;
    while (second != nullptr && cnt != pow) {
        if (second == first) {
            return pow - cnt;
        }
        second = second->ancestor;
        cnt++;
    }
    return -1;
}

node *lsa(node *first, node *second) {
    int pow = 1;
    int distance;
    while (1){
        distance = up(first, second, pow);
        if (distance != -1) break;
        distance = up(second, first, pow);
        if (distance != -1) {
            std::swap(first, second);
            break;
        }
        pow *= 2;
    }
    while (distance > 0) {
        first = first->ancestor;
        distance--;
    }
    while (first != second) {
        first = first->ancestor;
        second = second->ancestor;
    }
    return first;
}
