#include <iostream>
using namespace std;

struct node {
	int key;
	node* left_child = NULL;
	node* right_child = NULL;
	node* ancestor = NULL;
};//assuming every node contains pointers to it's children and ancestors
  //(the root's ancestor will point to NULL)

/****************************************************************************************
This function accepts three nodes - the root of the tree, and the two nodes we want to find
the common ancestor of.
how does she do it?
It goes over all of the second node's ancestor and compares them with all of the first node's 
ancestors.
Worst case scenario - both of the nodes are at the end of the tree - which meens we'll have 
to compare log(n) [n is num of nodes in the tree] ancestors with log(n) ancestors - les then o(n)
*****************************************************************************************/
node* find_common_anc(const node& tree_root,const node& first_node, const node& second_node) {
	//Since I don't want to change the original nodes(ans can't - because they're const)
	//I am using temporary nodes which I can change
	node const_second = second_node;
	node temp_first = first_node;
	node temp_second = second_node;
	node temp_tree_root = tree_root;
	//I wan't this loop to keep going until the ancestor is found - so while(1) ;)
	while (1) {
		if ((first_node.key == tree_root.key) || (second_node.key == tree_root.key)){
			cout << "one of the nodes is the root - which doesn't have an ancestor" << endl;
			//edge case - if someone sends the root- it doesn't have an ancestor - because he is the ancestor
			return &temp_tree_root;
		}
		if (temp_second.key == tree_root.key) {//if when we went over all of the ancestors
			//of the second node and reached the root, we'll start the second iteration - 
			//the first node we'll go up to it's ancestor, and the second we'll go back to it's original value
			temp_first = *temp_first.ancestor;
			temp_second = const_second;
		}
		//if it's not the same ancestor - go to the upper ancestor
		else if (temp_first.ancestor->key != temp_second.ancestor->key)
			temp_second = *temp_second.ancestor;
		//else - it is the one we were looking for, return it.
		else {
			return temp_first.ancestor;
		}
	}
}

int main() {

	node root;
	root.key = 7;
	node left;
	left.key = 3;
	root.left_child = &left;
	left.ancestor = &root;
	node right;
	right.key = 4;
	root.right_child = &right;
	right.ancestor = &root;
	node left_left;
	left_left.key = 2;
	left_left.ancestor = &left;
	node left_left_left;
	left_left_left.key = 1;
	left_left_left.ancestor = &left_left;
	node left_left_right;
	left_left_right.key = 6;
	left_left_right.ancestor = &left_left;
	node left_right;
	left_right.key = 5;
	left_right.ancestor = &left;
	node right_right;
	right_right.key = 8;
	right_right.ancestor = &right;
	right.right_child = &right_right;
	left.left_child = &left_left;
	left.right_child = &left_right;
	left_left.right_child = &left_left_right;
	left_left.left_child = &left_left_left;
	//test1
	node* ancestor =find_common_anc(root, left_left_left, left_right);
	cout << ancestor->key<<endl;
	//test2
	ancestor =find_common_anc(root, left_left_left, right_right);
	cout << ancestor->key<<endl;
	//test3
	ancestor = find_common_anc(root, left_left_left, left_left_left);
	cout << ancestor->key<<endl;
	//test4
	ancestor = find_common_anc(root, root, left_left_left);
	cout << ancestor->key<<endl;
	//test5
	ancestor = find_common_anc(root, left_left_left,root);
	cout << ancestor->key << endl;
	//test6
	ancestor = find_common_anc(root, left_left_right, left_right);
	cout << ancestor->key<<endl;
	cin >> ancestor->key;
	return 0;
