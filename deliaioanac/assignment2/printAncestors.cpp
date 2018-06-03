#include <iostream>
#include <vector>

// Structure for a tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(int x, TreeNode *p) : val(x), left(nullptr), right(nullptr), parent(p) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
};

// Class for binary tree
class BinaryTree {
    private:
        TreeNode *tree;
        TreeNode *dfsFind(TreeNode *node, const int val);
    public:
        TreeNode* createTree(const std::vector<int> &values, int k = 0, TreeNode *parent = nullptr);
        void destroyTree();
        void printAncestors(const int val);
};

// Populates binary tree with the values from the vector
// The current node has the value at position k and a pointer to the parent node
TreeNode* BinaryTree::createTree(const std::vector<int> &values, int k, TreeNode *parent) {
    // Check if there are any values to use for the nodes
    if (values.empty() || k > values.size()) {
        return nullptr;
    }

    // If this is true, then this is the first iteration of the function,
    // which initializes the tree member of the BinaryTree class
    if (k == 0) {
        tree = createTree(values, 1);
        return nullptr;
    }
    
    // Initialize the current node if kth value
    TreeNode *node = new TreeNode(values[k - 1], parent);
    // Initialize child nodes with appropriate values
    node->left = createTree(values, k * 2, node);
    node->right = createTree(values, k * 2 + 1, node);

    return node;
}

// Destry the binary tree recursively
void BinaryTree::destroyTree() {
    delete tree;
}

// Returns the tree node that holds this value
TreeNode* BinaryTree::dfsFind(TreeNode *node, const int val) {
    // Check if the node could not be found in this (sub)tree
    if (!node) {
        return nullptr;
    }

    // Check if the node was found
    if (node->val == val) {
        return node;
    }

    // If the node was found in the left subtree, return it
    // Otherwise, return the result of the search in the right subtree
    TreeNode *result = dfsFind(node->left, val);
    return (result ? result : dfsFind(node->right, val));
}

// Prints all ancestors of the node with this value, bottom-up
void BinaryTree::printAncestors(const int val) {
    // Find the tree node holding this value
    TreeNode *node = dfsFind(tree, val);

    // If it exists, go to parent to start printing ancestors
    if (node) {
        node = node->parent;
    // If it does no exist, signal that to the user
    } else {
        std::cout << "Please enter a valid node!" << std::endl;
        return;
    }
    
    // Go up the tree and print the values held by the ancestors
    while (node) {
        std::cout << node->val;
        node = node->parent;
        if (node) {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
}
