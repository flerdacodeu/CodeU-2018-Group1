#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
/*#include "gtest/gtest.h"*/
#include <vector>

using namespace std;

int n, cur_anc;
vector<int> par;

struct Node {
	Node * anc;
	int num;
};

vector<Node *> nodes;

vector<int> get_parents(Node * cur_node) {
	vector<int> ans;
	while ((cur_node -> anc) != NULL) {
		ans.push_back(cur_node->anc->num);
		cur_node = cur_node -> anc;
	}
	return ans;
}

int get_min_anc(Node * f_node, Node * s_node) {
	vector<int> f_way = get_parents(f_node);
	vector<int> s_way = get_parents(s_node);
	reverse(f_way.begin(), f_way.end());
	reverse(s_way.begin(), s_way.end());
	int ans = 0;
	int f_size = f_way.size();
	int s_size = s_way.size();
	while((ans + 1) < f_size && (ans + 1) < s_size && f_way[ans + 1] == s_way[ans + 1]) 
		ans++;
	return f_way[ans];
}

int main() {
	par.push_back(0);
	nodes.push_back(NULL);
	freopen("Test.txt", "r", stdin);
	while (cin >> cur_anc) { //decide that in every string we have a parent of cur num
		par.push_back(cur_anc);
		n++;
		Node * new_node = new Node();
		new_node->num = n;
		nodes.push_back(new_node);
	}
	for (int i = 1; i <= n; i++) {
		if (par[i] != 0) {
			nodes[i]->anc = nodes[par[i]];	
		}
	} 
	int ans1[] = {2, 3, 7};
	vector<int> pr_ans = get_parents(nodes[6]);
	if (equal(pr_ans.begin(), pr_ans.end(), ans1))
		cout << "Test1 is OK\n";
	else 
		cout << "Test1 is FAILED\n";
	if (3 == get_min_anc(nodes[1], nodes[5]))
		cout << "Test2 is OK\n";
	else
	        cout << "Test1 is FAILED\n";

	return 0;
}
