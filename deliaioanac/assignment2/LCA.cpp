#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <utility>
#include <stdlib.h>


// Structure for a tree node
struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
    TreeNode(int x) : val(x) {}
    ~TreeNode() {
        while (!children.empty()) {
            delete children.back();
            children.pop_back();
        }
    }
};

// Structure for tree representation
class CustomTree {
    private:
        TreeNode* tree;
        std::vector<int> first, eulerNodes, eulerLevels;
        std::vector<std::vector<int> > rmq;
        void makeEuler(TreeNode *node, int level);
        void makeRMQ();
    public:
        void createTree(const std::vector<int> &parents, int &k, TreeNode *node = nullptr);
        void destroyTree();
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
void CustomTree::createTree(const std::vector<int> &parents, int &k, TreeNode *node) {
    // This is the first iteration, so the root is initialized
    if (k == 1) {
        tree = new TreeNode(1);
        if (!tree) {
            std::cerr << "new failed" << std::endl;
            return;
        }

        k ++;
        // This holds the position of the first appearance
        // of each node in the Euler representation
        first = std::vector<int>(parents.size() + 2);
        createTree(parents, k, tree);
    }

    // Check if there are any nodes left to create
    if (k - 2 >= parents.size()) {
        return;
    }

    // While the current node is the parent of the next node to be created,
    // add it to the list of children of the current node
    while (k - 2 < parents.size() && parents[k - 2] == node->val) {
        TreeNode *newNode = new TreeNode(k);
        if (!newNode) {
            std::cerr << "new failed" << std::endl;
            return;
        }

        node->children.push_back(newNode);
        k ++;
    }

    // Find the parent for the next node to be inserted
    for (auto c : node->children) {
        if (c->val == parents[k - 2]) {
            createTree(parents, k, c);
        }
    }
}

// Destroys the entire tree recursively
void CustomTree::destroyTree() {
    delete tree;
}

// Computes the Euler representation of the tree
void CustomTree::makeEuler(TreeNode *node, int level) {
    eulerNodes.push_back(node->val);
    eulerLevels.push_back(level);
    first[node->val] = eulerNodes.size() - 1;

    for (auto c : node->children) {
        makeEuler(c, level + 1);
        eulerNodes.push_back(node->val);
        eulerLevels.push_back(level);
    }
}

// Computes the RMQ table for the Euler representation
void CustomTree::makeRMQ() {
    int eulerSize = eulerLevels.size();
    int logOfEulerSize = (int)(log(eulerSize) / log(2));

    rmq = std::vector<std::vector<int> > (eulerSize, std::vector<int>(logOfEulerSize + 1));

    for (int i = 0; i < eulerSize; i ++) {
        rmq[i][0] = i;
    }

    for (int j = 1; j <= logOfEulerSize; j ++) {
        for (int i = 0; i < eulerSize - (1 << (j - 1)); i ++) {
            if (eulerLevels[rmq[i][j - 1]] < eulerLevels[rmq[i + (1 << (j - 1))][j - 1]]) {
                rmq[i][j] = rmq[i][j - 1]; 
            }
            else {
                rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

// Does the preprocessing in O(n * log(n)) time, where n is the number of nodes
// With this data, the LCA of any two nodes can be obtained in constant time at every query
// The only potential disadvantage is the O(n * log(n)) space complexity
void CustomTree::preprocessingLCA() {
    makeEuler(tree, 0);
    makeRMQ();
}

// Gets the lowest common ancestor of any two nodes in constant time
int CustomTree::getLowestCommonAncestor(int node1, int node2) {
    if (node1 < 1 || node1 >= first.size() || node2 < 1 || node2 >= first.size()) {
        std::cerr << "Node index is invalid!" << std::endl;
        return 0;
    }

    int firstNode1 = first[node1], firstNode2 = first[node2];
    int range = abs(firstNode2 - firstNode1) + 1;
    int logOfRange = (int)(log(range) / log(2));
    int lca = rmq[std::min(firstNode1, firstNode2)][logOfRange];

    range -= (1 << logOfRange);

    if (range != 0 && eulerLevels[lca] >=
        eulerLevels[rmq[std::min(firstNode1, firstNode2) + range][logOfRange]])
        lca = rmq[std::min(firstNode1, firstNode2) + range][logOfRange];
    
    return eulerNodes[lca];
}
