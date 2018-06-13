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
	std::vector<int> GetAncestors(int key) {
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
	int LowestCommonAncestor (Node* node1, Node* node2) {
		std::vector<int> ancestors_node1 = GetAncestors(node1->data);
		std::vector<int> ancestors_node2 = GetAncestors(node2->data);
		int difference_size = std::max(ancestors_node1.size(), ancestors_node2.size()) - std::min(ancestors_node1.size(), ancestors_node2.size());
		int i, j; 
		if (ancestors_node1.size() > ancestors_node2.size()) {
			i = difference_size;
			j = 0;
		}
		else {
			i = 0;
			j = difference_size;
		}
		for (; i < ancestors_node1.size(); i++) 
			for (; j < ancestors_node2.size(); j++)
				if (ancestors_node1[i] == ancestors_node2[j])
					return ancestors_node1[i];
		return -19090909;
	}
};
int main (void) {
	Tree tree = Tree(); 
	tree.CreateRoot(1);

	Node* node3 = tree.CreateNode(3);
	tree.AppendTree(tree.root, node3, false);

	Node* node2 = tree.CreateNode(2);
	tree.AppendTree(node3, node2, true);

	Node* node4  = tree.CreateNode(4);
	tree.AppendTree(node3, node4, false);
	
	int lowest_common_ancestor = tree.LowestCommonAncestor(node4,node2);

	std::cout << lowest_common_ancestor << std::endl; 
	
	return 0;
}