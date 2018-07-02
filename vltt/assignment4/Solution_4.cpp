#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <string>
#include <memory>

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" << #actual << ") is " << actual            \
              << ", expected " << (expected) << " (" << #expected << ")." \
              << std::endl;                                               \
  } else {                                                                \
    std::cout << __FILE__ << ":" << __LINE__ << " True " << std::endl;  \
  }

template <class T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
	os << "{";
	for (auto &it : s) {
		os << it;
		std::cout << ", ";
	}
	os << "}";
	return os;
}


void make_set(int num_island, std::vector<int> &parent, std::vector<int> &rank) {
	parent[num_island] = num_island;
	rank[num_island] = 0;
}

int find_set(int num_island, std::vector<int> &parent) {
	if (num_island == parent[num_island])
		return num_island;
	return parent[num_island] = find_set(parent[num_island], parent);
}

void union_sets(int num_island_a, int num_island_b, std::vector<int> &parent, std::vector<int> &rank) {
	num_island_a = find_set(num_island_a, parent);
	num_island_b = find_set(num_island_b, parent);
	if (num_island_a != num_island_b) {
		if (rank[num_island_a] < rank[num_island_b])
			std::swap(num_island_a, num_island_b);
		parent[num_island_b] = num_island_a;
		if (rank[num_island_a] == rank[num_island_b])
			++rank[num_island_a];
	}
}

//disjoint-set-union (with path compression and union by rank)
int number_of_islands(int n, int m, std::vector<std::vector<bool> > &location_of_isl){
	std::vector<int> parent(n * m, -1);
	std::vector<int> rank(n * m, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (location_of_isl[i][j]) {
				int num_cur = i * m + j;
				make_set(num_cur, parent, rank);
				int num_left = -1;
				int num_up = -1;
				//left
				if (j != 0 && location_of_isl[i][j - 1]) {
					num_left = find_set(i * m + j - 1, parent);
					union_sets(num_left, num_cur, parent, rank);
				}
				//up
				if (i != 0 && location_of_isl[i - 1][j]) {
					num_up = find_set((i - 1) * m + j, parent);
					//to merge different parts of the island
					union_sets(num_up, num_cur, parent, rank);
				}
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n * m; i++) {
		if (parent[i] == i) cnt++;
	}
	return cnt;
}


void simpleTest() {
	std::vector< std::vector<bool> > first_input = { {0, 1, 0, 1},
											         {1, 1, 0, 0},
											         {0, 0, 1, 0},
											         {0, 0, 1, 0} };
	std::vector< std::vector<bool> > second_input = { { 0, 0, 1, 1 },
											          { 1, 0, 1, 0 },
											          { 1, 1, 1, 0 } };
	EXPECT_EQ(3, number_of_islands(first_input.size(), first_input[0].size(), first_input));
	EXPECT_EQ(1, number_of_islands(second_input.size(), second_input[0].size(), second_input));
	
}
void emptyTest() {
	std::vector< std::vector<bool> >  input = {};
	EXPECT_EQ(0, number_of_islands(0, 0, input));
}

void onlyLandTest() {
	std::vector< std::vector<bool> > input(10, std::vector<bool>(7));
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[0].size(); j++) {
			input[i][j] = 1;
		}
	}
	EXPECT_EQ(1, number_of_islands(input.size(), input[0].size(), input));
}

void onlyWaterTest() {
	std::vector< std::vector<bool> > input(17, std::vector<bool>(5));
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[0].size(); j++) {
			input[i][j] = 0;
		}
	}
	EXPECT_EQ(0, number_of_islands(input.size(), input[0].size(), input));
}


void tests() {
	simpleTest();
	emptyTest();
	onlyLandTest();
	onlyWaterTest();
}

int main() {
	tests();
	system("pause");
}

