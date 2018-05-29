#include <iostream>
#include <algorithm>
#include <iomanip>

struct node {
    node *left = nullptr;
    node *right = nullptr;
    int value;
};

bool dfs(const int key, const node *cur) {
    if (cur == nullptr) return false;
    if (cur->value == key) {
        return true;
    }
    bool is_found = dfs(key, cur->left) || dfs(key, cur->right);
    if (is_found) std::cout << cur->value << ' ';
    return is_found;
}
void ancestors_of_key(const int key, const node *root) {
    dfs(key, root);
    std::cout << std::endl;
}
