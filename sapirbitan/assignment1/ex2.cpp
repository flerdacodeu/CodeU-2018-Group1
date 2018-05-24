#include <iostream>
#include <string>
using namespace std;

struct Node {
	int num;
	Node* next_node=NULL;
};
/* I am assuming each element in the linked list contains a pointer to the next element in the list,
also, I am assuming my function gets the "head" of the linked list and 'k'	*/

Node find_kth_element(Node& head, int k) {
	int num_of_elements = 1;
	Node* current = &head;
	//finds out how many elements are on the linked list
	while (current->next_node != NULL) {
		num_of_elements += 1;
		current = current->next_node;
	}
	//if k>num_of_elements the function will return the "head" of the list
	Node kth = head;// the kth last element
	//"going" to the kth last element
	for (int i = 1; i < num_of_elements-k;i++) {
		kth = *kth.next_node;
	}
	return kth;
}

int main() {
	Node a;
	a.num = 21;
	Node b;
	a.next_node = &b;
	b.num = 20;
	Node c;
	b.next_node = &c;
	c.num = 19;
	Node d;
	c.next_node = &d;
	d.num = 18;
	Node e;
	d.next_node = &e;
	e.num = 17;
	//test1
	Node kth = find_kth_element(a, 6);
	cout << kth.num << endl;
	//test2
	kth = find_kth_element(a, 5);
	cout << kth.num << endl;
	//test3
	kth = find_kth_element(c, 2);
	cout << kth.num << endl;
}
