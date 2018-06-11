#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <utility>
#include <stdlib.h>
#include <memory>


// Structure for a tree node
struct TreeNode {
    int val;
    std::vector<std::unique_ptr<TreeNode> > children;
    TreeNode(int x) : val(x) {}
};

// Structure for tree representation
class CustomTree {
    private:
        std::unique_ptr<TreeNode> tree_;
        std::vector<int> first_, eulerNodes_, eulerLevels_;
        std::vector<std::vector<int> > rmq_;
        void createTreeHelper(const std::vector<int> &parents, int &k, std::unique_ptr<TreeNode> &node);
        void makeEuler(std::unique_ptr<TreeNode> node, int level);
        void makeRMQ();
    public:
        CustomTree(const std::vector<int> &parents);
        void preprocessingLCA();
        int getLowestCommonAncestor(int node1, int node2);
};

// Creates new tree based on parents vector
// The ith element (1 <= i) is the index of the parent of the (i + 1)th node
// (the offset is due to the fact that node 1 has no parent)
// The elements are ordered such that they can be inserted in a bfs-like order
// Example : {1, 1, 2, 2, 3, 3} generates the following tree :
//                     1
//                    / \
//                   2   3
//                  / \  /\
//                 4  5 6  7
void CustomTree::createTreeHelper(const std::vector<int> &parents, int &k, std::unique_ptr<TreeNode> &node) {
    // This is the first iteration, so the root is initialized
    if (k == 1) {
        this->tree_ = std::unique_ptr<TreeNode>(new TreeNode(1));
        k ++;
        // This holds the position of the first appearance
        // of each node in the Euler representation
        this->first_ = std::vector<int>(parents.size() + 2);
        createTreeHelper(parents, k, this->tree_);
    }

    // Check if there are any nodes left to create
    if (k - 2 >= parents.size()) {
        return;
    }

    // While the current node is the parent of the next node to be created,
    // add it to the list of children of the current node
    while (k - 2 < parents.size() && parents[k - 2] == node->val) {
        std::unique_ptr<TreeNode> newNode(new TreeNode(k));
        node->children.push_back(std::move(newNode));
        k ++;
    }

    // Find the parent for the next node to be inserted
    for (auto &c : node->children) {
        if (c->val == parents[k - 2]) {
            createTreeHelper(parents, k, c);
        }
    }
}

CustomTree::CustomTree(const std::vector<int> &parents) {
    int start = 1;
    createTreeHelper(parents, start, this->tree_);
}

// Computes the Euler representation of the tree
void CustomTree::makeEuler(std::unique_ptr<TreeNode> node, int level) {
    eulerNodes_.push_back(node->val);
    eulerLevels_.push_back(level);
    first_[node->val] = eulerNodes_.size() - 1;

    for (auto &c : node->children) {
        makeEuler(std::move(c), level + 1);
        eulerNodes_.push_back(node->val);
        eulerLevels_.push_back(level);
    }
}

// Computes the RMQ table for the Euler representation
void CustomTree::makeRMQ() {
    int eulerSize = eulerLevels_.size();
    int logOfEulerSize = (int)(log(eulerSize) / log(2));

    rmq_ = std::vector<std::vector<int> > (eulerSize, std::vector<int>(logOfEulerSize + 1));

    for (int i = 0; i < eulerSize; i ++) {
        rmq_[i][0] = i;
    }

    for (int j = 1; j <= logOfEulerSize; j ++) {
        for (int i = 0; i < eulerSize - (1 << (j - 1)); i ++) {
            if (eulerLevels_[rmq_[i][j - 1]] < eulerLevels_[rmq_[i + (1 << (j - 1))][j - 1]]) {
                rmq_[i][j] = rmq_[i][j - 1]; 
            }
            else {
                rmq_[i][j] = rmq_[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

// Does the preprocessing in O(n * log(n)) time, where n is the number of nodes
// With this data, the LCA of any two nodes can be obtained in constant time at every query
// The only potential disadvantage is the O(n * log(n)) space complexity
void CustomTree::preprocessingLCA() {
    makeEuler(std::move(tree_), 0);
    makeRMQ();
}

// Gets the lowest common ancestor of any two nodes in constant time
int CustomTree::getLowestCommonAncestor(int node1, int node2) {
    if (node1 < 1 || node1 >= first_.size() || node2 < 1 || node2 >= first_.size()) {
        std::cerr << "Node index is invalid!" << std::endl;
        return 0;
    }

    int firstNode1 = first_[node1], firstNode2 = first_[node2];
    int range = abs(firstNode2 - firstNode1) + 1;
    int logOfRange = (int)(log(range) / log(2));
    int lca = rmq_[std::min(firstNode1, firstNode2)][logOfRange];

    range -= (1 << logOfRange);

    if (range != 0 && eulerLevels_[lca] >=
        eulerLevels_[rmq_[std::min(firstNode1, firstNode2) + range][logOfRange]])
        lca = rmq_[std::min(firstNode1, firstNode2) + range][logOfRange];
    
    return eulerNodes_[lca];
}
