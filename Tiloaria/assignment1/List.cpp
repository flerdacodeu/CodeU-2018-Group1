#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

struct List {
        List * next = nullptr;
	int num;
        List (int new_num) {
		num = new_num;
	}
};

void new_head(List ** head, List * elem) {
    elem -> next = *head;
    *head = elem;
}

List * k_last_elem (List * first, int k) {
        if (k < 0)
            return nullptr;
	int n = 0;
	List * cur = first;
        while (cur != nullptr) {
		n++;
		cur = cur -> next;
	}
        if (n <= k)
                return nullptr;
	List * ans = first;
	for (int i = 1; i < (n - k); i++) {
                ans = ans -> next;
        }
        return ans;
}

int main() {
        List * head = nullptr;
        vector<List> a;
        for (int i = 0; i <= 10; i++) {
            a.push_back(*(new List(i + 1)));
        }
        for (int i = 10; i >= 0; i--) {
            new_head(&head, &a[i]);
        }
        if (k_last_elem(head, 0) == &a[10])
		cout << "Test 1 done\n";
	else
		cout << "Test 1 failed\n";
        if (k_last_elem(head, 4) == &a[6])
		cout << "Test 2 done\n";
	else
		cout << "Test 2 failed\n";

	return 0;
}
