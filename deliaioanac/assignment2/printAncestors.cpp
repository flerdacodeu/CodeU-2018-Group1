#include <iostream>
#include <vector>
#include <memory>

// Structure for a tree node
struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Class for binary tree
class BinaryTree {
    private:
        std::unique_ptr<TreeNode> tree_;
        std::unique_ptr<TreeNode> dfsFind(std::unique_ptr<TreeNode> node, const int val, std::vector<int> &parents);
        std::unique_ptr<TreeNode> createTreeHelper(const std::vector<int> &values, int k);
    public:
        BinaryTree(const std::vector<int> &values);
        void printAncestors(const int val);
};

std::unique_ptr<TreeNode> BinaryTree::createTreeHelper(const std::vector<int> &values, int k) {
    // Check if there are any values to use for the nodes
    if (values.empty() || k > values.size()) {
        return nullptr;
    }

    // Initialize the current node if kth value
    std::unique_ptr<TreeNode> node(new TreeNode(values[k - 1]));
    // Initialize child nodes with appropriate values
    node->left = createTreeHelper(values, k * 2);
    node->right = createTreeHelper(values, k * 2 + 1);

    return node;
}

// Populates binary tree with the values from the vector
// The current node has the value at position k and a pointer to the parent node
BinaryTree::BinaryTree(const std::vector<int> &values) {
    this->tree_ = createTreeHelper(values, 1);
}

// Returns the tree node that holds this value
std::unique_ptr<TreeNode> BinaryTree::dfsFind(std::unique_ptr<TreeNode> node, const int val, std::vector<int> &parents) {
    // Check if the node could not be found in this (sub)tree
    if (!node) {
        return nullptr;
    }

    // Check if the node was found
    if (node->val == val) {
        return node;
    }

    parents.push_back(node->val);

    // If the node was found in the left subtree, return it
    // Otherwise, return the result of the search in the right subtree
    std::unique_ptr<TreeNode> result = dfsFind(std::move(node->left), val, parents);
    if (result) {
        return result;
    }

    result = dfsFind(std::move(node->right), val, parents);
    if (result) {
        return result;
    }

    parents.pop_back();
    return nullptr;
}

// Prints all ancestors of the node with this value, bottom-up
void BinaryTree::printAncestors(const int val) {
    // Find the tree node holding this value
    std::vector<int> parents;
    std::unique_ptr<TreeNode> node = dfsFind(std::move(this->tree_), val, parents);

    // If it does no exist, signal that to the user
    if (!node) {
        std::cout << "Please enter a valid node!" << std::endl;
        return;
    }
    
    // Go up the tree and print the values held by the ancestors
    for (int i = parents.size() - 1; i >= 0; i --) {
        std::cout << parents[i];
        if (i) {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
}
