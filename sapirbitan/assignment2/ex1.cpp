#include <iostream>
using namespace std;

struct node {
	int key;
	node* left_child = nullptr;
	node* right_child = nullptr;
	node* ancestor = nullptr;
};//assuming every node contains pointers to it's children and ancestors
  //(the root's ancestor will point to nullptr)

// this function finds the key which we want to print it's ancestors from
//it goes over all of the tree and returns the node we were looking for
node* find_key(node& root, int& key) {
	node* found_key = nullptr;
	if (&root == nullptr) 
		return nullptr;
	if (root.key == key)
		return &root;
	//since it's a binary tree - we have to go in two paths - left and right
	found_key = find_key(*(root.left_child), key);//left
	if (found_key != nullptr)
		return found_key;
	found_key = find_key(*(root.right_child), key);//right
	if (found_key != nullptr)
		return found_key;
	return nullptr;// if we haven't found anything - return nullptr
}

//this function prints the key's ancestors
void print_anc(node& key){
	if (key.ancestor == nullptr) {//since the only node that has no ancestor is the root
		cout << "root does not have ancestors" << endl;
	}
	node current_node = key;
	while (current_node.ancestor != nullptr) {
		cout << current_node.ancestor->key<< "\n";
		current_node = *current_node.ancestor;
	}

}
void testing(node& root) {
	//test1 - should print - 2 3 7
	int num = 6;
	node* key = find_key(root, num);
	cout << "test 1: key = " <<num<<" - should print - 2 3 7"<< endl;
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
	//test2 - should print - 3 7
	num = 5;
	cout << "test 2: key = " << num << " - should print - 3 7" << endl;
	key = find_key(root, num);
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
	//test3 - should print - 4 7
	num = 8;
	cout << "test 3: key = " << num << " - should print - 4 7" << endl;
	key = find_key(root, num);
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
	//test4 - should print "root does not have ancestors"
	num = 7;
	cout << "test 4: key = " << num << " - should print - root does not have ancestors" << endl;
	key = find_key(root, num);
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
	//test5 - should print - 2 3 7
	num = 1;
	cout << "test 5: key = " << num << " - should print - 2 3 7" << endl;
	key = find_key(root, num);
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
	//test6 - should print - "the key does not exist in this tree"
	num = 13;
	cout << "test 6: key = " << num << " - should print - the key does not exist in this tree" << endl;
	key = find_key(root, num);
	if (key != nullptr)
		print_anc(*key);
	else
		cout << "the key does not exist in this tree";
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
	/*
							7
						/		\
					       3		 4
					/		\		\
				       2		  5		 8 
				/		\
			      1		        6
	
	
	*/
	testing(root);
}
