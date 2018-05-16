#include <iostream>

struct node {
    node *next = nullptr;
    int x;
};

node *kth_elem(node *root, int k) {
    if (root == nullptr) return nullptr;
    node *slow = root, *fast = root->next;
    while (k && fast != nullptr) {
        fast = fast->next;
        k--;
    }
    if (k) return nullptr;
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
