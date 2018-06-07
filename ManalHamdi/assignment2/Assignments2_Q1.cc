#include <iostream>
#include <queue>
#include <vector>

struct Node {
	int data;
	Node* parent;
	Node* left_child;
	Node* right_child; 
};
class Tree {
public:
	Node* root;
	Tree() {
		root = nullptr;
	}
	Node* CreateNode(int data) {
		Node* temp = new Node;
		temp->data = data;
		temp->left_child = nullptr;
		temp->right_child = nullptr;
		temp->parent = nullptr;
		return temp;
	} 
	void AppendTree(Node* parent, Node* node_to_append, bool append_to_left) {
		node_to_append->parent = parent;
		if (append_to_left) {
			parent->left_child = node_to_append;
		}
		else
			parent->right_child = node_to_append;
	}
	void CreateRoot(int data) {
		root = CreateNode(data);
		root->parent = nullptr;
	}
	std::vector<int> PrintAncestors(int key) {
		std::vector<int> ancestors;
		if (root == nullptr || root->data == key)
			return ancestors;
		std::queue <Node*> q; 
		q.push(root);
		while (!q.empty()) {
			Node* current_node = q.front(); 
			q.pop();
			if (current_node->data == key) {
				Node* parent_node = current_node->parent;
				while (parent_node != nullptr ) {
					ancestors.push_back(parent_node->data);
					parent_node = parent_node->parent;
				}
				return ancestors;
			} 
			else {
				if (current_node->left_child)
					q.push(current_node->left_child);
				if (current_node->right_child)
					q.push(current_node->right_child);
			}
		}
		return ancestors;
	}
};

int main (void) {
	Tree tree = Tree(); 
	tree.CreateRoot(1);

	Node* node2 = tree.CreateNode(2);
	tree.AppendTree(tree.root, node2, true);

	Node* node3 = tree.CreateNode(3);
	tree.AppendTree(tree.root, node3, false);
	
	std::vector<int> ancestors = tree.PrintAncestors(3);
	
	if (ancestors.size() == 0)
		std::cout << "No ancestors for the given key were found; either the key is not in the tree or it doesnt have parents (root)" << std::endl;
	else
		for (int i = 0; i < (int)ancestors.size(); i++) 
			std::cout << ancestors[i] << " "; 
	
	return 0;
}