#include <iostream>
#include <string>
using namespace std;

struct some_struct {
	int num;
	some_struct* s=NULL;
};
/* I am assuming each element in the linked list contains a pointer to the next element in the list,
also, I am assuming my function gets the "head" of the linked list and 'k'	*/

some_struct find_kth_element(some_struct first_element, int k) {
	int num_of_elements = 1;
	some_struct* current = &first_element;
	//if k>num_of_elements the function will return the "head" of the list
	some_struct kth=first_element;// the kth last element
	//finds out hoe many elements are on the linked list
	while (current->s!= NULL) {
		num_of_elements += 1;
		current = current->s;
	}
	//"going" to the kth last element
	for (int i = 1; i < num_of_elements-k;i++) {
		kth = *kth.s;
	}
	return kth;
}
int main() {
	//test
	some_struct a;
	a.num = 21;
	some_struct b;
	a.s = &b;
	b.num = 20;
	some_struct c;
	b.s = &c;
	c.num = 19;
	some_struct d;
	c.s = &d;
	d.num = 18;
	some_struct e;
	d.s = &e;
	e.num = 17;
	some_struct kth = find_kth_element(a, 6);
	cout << kth.num;
}
