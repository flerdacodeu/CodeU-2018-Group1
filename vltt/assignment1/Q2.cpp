#include <iostream>

struct node {
    node *next = nullptr;
    int value;
};

node *kth_elem(const node *root, int k) {
    if (root == nullptr || k < 0) return nullptr;
    node *slow = root, *fast = root->next;
    while (k > 0 && fast != nullptr) {
        fast = fast->next;
        k--;
    }
    if (k > 0) return nullptr;
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
