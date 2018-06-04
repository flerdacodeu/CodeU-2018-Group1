#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

struct node {
    node *left = nullptr;
    node *right = nullptr;
    int value;
};

// dfs implements the depth-first search algorithm, put all of the ancestors of the given key in the vector.
// dfs assumes that the given tree only contains unique nodes.
bool dfs(const int key, const node *cur, std::vector<const node*> &vector_of_ancestors) {
    if (cur == nullptr) return false;
    if (cur->value == key) {
        return true;
    }
    bool is_found = dfs(key, cur->left, vector_of_ancestors) || dfs(key, cur->right, vector_of_ancestors);
    if (is_found) vector_of_ancestors.push_back(cur);
    return is_found;
}
std::vector<const node*>  ancestors_of_key(const int key, const node *root) {
    std::vector<const node*> vector_of_ancestors;
    dfs(key, root, vector_of_ancestors);
    reverse(vector_of_ancestors.begin(), vector_of_ancestors.end());
    return vector_of_ancestors;
}
