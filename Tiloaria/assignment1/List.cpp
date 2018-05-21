#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

struct List {
	List * next = 0;
	int num;
	List () {}
	List (List * new_next, int new_num) {
		next = new_next;
		num = new_num;
	}
};

List * k_last_elem (List * first, int k) {
	int n = 0;
	List * cur = first;
	while (cur != 0) {
		n++;
		cur = cur -> next;
	}
	if (n <= k) 
		return 0;
	List * ans = first;
	for (int i = 1; i < (n - k); i++) {
		ans = ans -> next;
	}
	return ans;
}

int main() {
	List a[11];
	a[10] = List(0, 11);
	for (int i = 0; i < 10; i++) {
		a[i] = List(&a[i + 1], i + 1);
	}
	if (k_last_elem(&a[0], 0) == &a[10])
		cout << "Test 1 done\n";
	else
		cout << "Test 1 failed\n";
	if (k_last_elem(&a[0], 4) == &a[6])
		cout << "Test 2 done\n";
	else
		cout << "Test 2 failed\n";

	return 0;
}
