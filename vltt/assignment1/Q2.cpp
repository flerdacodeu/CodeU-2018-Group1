#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct list {
    list *next = nullptr;
    int x;
};

list *kth_elem(list *root, int k) {
    if (root == nullptr) return nullptr;
    list *l = root, *r = root->next;
    while (k && r != nullptr) {
        r = r->next;
        k--;
    }
    if (k) return nullptr;
    while (r != nullptr) {
        r = r->next;
        l = l->next;
    }
    return l;
}
