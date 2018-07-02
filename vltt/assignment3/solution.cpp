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

class Dictionary {
private:
	class Trie {
	private:
		class Node {
		private:
			std::map<char, std::shared_ptr<Node>> children;
		public:
			bool terminal = false;
			void add(char letter) {
				children[letter] = std::shared_ptr<Node>(new Node);
			}
			bool isHere(char letter) {
				return children.find(letter) != children.end();
			}
			std::shared_ptr <Node> next(char letter) {
				if (children.find(letter) == children.end()) return nullptr;
				return children[letter];
			}
		};
		std::shared_ptr<Node> start;
	public:
		Trie() {
			start = std::shared_ptr<Node>(new Node);
		}
		//add new word to the Trie
		void add(const std::string &word) {
			if (word.empty()) return;
			std::shared_ptr<Node> cur = start;
			for (int i = 0; i < word.length(); i++) {
				char letter = word[i];
				if (!cur->isHere(letter)) {
					cur->add(letter);
				}
				cur = cur->next(letter);
				if (i == int(word.length()) - 1) {
					cur->terminal = true;
				}
			}
		}
		//determines whether there is such a prefix in the Trie
		//return: -1 - prefix, 0 - nothing, 1 - word
		int find_str(const std::string &str) const {
			if (str.empty()) return 0;
			std::shared_ptr<Node> cur = start;
			for (int i = 0; i < str.length(); i++) {
				if (cur == nullptr) break;
				char letter = str[i];
				cur = cur->next(letter);
				if (i == int(str.length()) - 1) {
					if (cur == nullptr) return 0;
					if (cur->terminal) return 1;
					else return -1;
				}
			}
			return 0;
		}
	};
	Trie prefixes;
public:
	Dictionary() {}
	Dictionary(const std::vector<std::string> all_words) {
		for (auto &word : all_words) {
			add(word);
		}
	}
	//add new word to the Dictionary
	void add(const std::string &word) {
		prefixes.add(word);
	}
	bool isWord(const std::string &cur) const {
		return prefixes.find_str(cur) == 1;
	}
	bool isPrefix(const std::string &cur) const {
		return prefixes.find_str(cur);
	}
};

bool in_bounds(int new_i, int new_j, const std::vector<std::vector<char> > &grid) {
	return new_i < 0 || new_i >= grid.size() || new_j < 0 || new_j >= grid[0].size();
}

//Recursively scans all words in the grid.
void passage_through_the_grid(const std::vector<std::vector<char> > &grid, const Dictionary &dict, std::string &cur_word, int i_gr, int j_gr, std::set<std::string> &ans, std::set<std::pair<int, int> > &used) {
	const std::vector<int> id_x = { 0, 1, -1 };
	const std::vector<int> id_y = { 0, 1, -1 };
	//These cycles handle all possible directions: right, left, up, down, diagonally
	for (int i = 0; i < id_x.size(); i++) {
		for (int j = 0; j < id_y.size(); j++) {
			if (i == 0 && j == 0) continue;
			int new_i = i_gr + id_x[i];
			int new_j = j_gr + id_y[j];
			//The coordinates of the letter that will potentially be the next letter in the word "cur_word"
			std::pair<int, int> new_coordinates = std::make_pair(new_i, new_j);
			if (in_bounds(new_i, new_j, grid)) continue;
			char next_letter = grid[new_i][new_j];
			//If there is a prefix in the "dict" -  "cur_word" + "next_letter"
			//then we will add "next_letter" to the "cur_word" and call this function
			//if not, then there is no sense to consider this new word
			if (dict.isPrefix(cur_word + next_letter) && used.find(new_coordinates) == used.end()) {
				if (dict.isWord(cur_word + next_letter)) ans.insert(cur_word + next_letter);
				cur_word.push_back(next_letter);
				used.insert(new_coordinates);
				passage_through_the_grid(grid, dict, cur_word, new_i, new_j, ans, used);
				used.erase(new_coordinates);
				cur_word.pop_back();
			}
		}
	}
}

std::set<std::string> words_of_dict_in_grid(const std::vector<std::vector<char> > &grid, const Dictionary &dict) {
	if (grid.size() == 0) return {};
	int m = grid[0].size();
	int n = grid.size();
	//Checks that the grid has a size N*M
	for (auto &it : grid) {
		if (it.size() != m) return {};
	}
	std::set<std::string> ans;
	std::set<std::pair<int, int> > used; //set for marking the cells of grid in which we already were
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::string cur = "";
			passage_through_the_grid(grid, dict, cur, i, j, ans, used);
		}
	}
	return ans;
}

void dictionaryTest() {
	std::vector<std::string> vec_of_str = { "car", "card", "cart", "cat", "meow" };
	Dictionary dict(vec_of_str);
	//test isWord
	for (auto &it : vec_of_str) {
		EXPECT_EQ(true, dict.isWord(it));
	}
	std::vector<std::string> false_words = { "carr", "carm", "ca", "c", "meoo", "gg", "", " " };
	for (auto &it : false_words) {
		EXPECT_EQ(false, dict.isWord(it));
	}
	//test isPrefix
	std::vector<std::string> vec_of_prfx = { "ca", "c", "car", "meow", "meo", "me" };
	for (auto &it : vec_of_prfx) {
		EXPECT_EQ(true, dict.isPrefix(it));
	}
	std::vector<std::string> false_prfx = { "carr", "carm", "g", "meoo", "", " " };
	for (auto &it : false_prfx) {
		EXPECT_EQ(false, dict.isPrefix(it));
	}

}

void simpleTest() {
	std::vector<std::string> vec_of_str = { "car", "card", "cart", "cat", "meow" };
	Dictionary dict(vec_of_str);
	std::vector<std::vector<char> > grid = { { 'a', 'a', 'r' },{ 't', 'c', 'd' },{ 'm', 'e', 'o' },{ 'm', 'e', 'w' } };
	std::set<std::string> expect = { "car", "card", "cat", "meow" };
	EXPECT_EQ(expect, words_of_dict_in_grid(grid, dict));
}
void emptyDictionaryTest() {
	std::vector<std::string> vec_of_str = {};
	Dictionary dict(vec_of_str);
	std::vector<std::vector<char> > grid = { { 'a', 'a', 'r' },{ 't', 'c', 'd' },{ 'm', 'e', 'o' },{ 'm', 'e', 'w' } };
	std::set<std::string> expect = {};
	EXPECT_EQ(expect, words_of_dict_in_grid(grid, dict));
}

void emptyGridTest() {
	std::vector<std::string> vec_of_str = { "car", "card", "cart", "cat", "meow" };
	Dictionary dict(vec_of_str);
	std::vector<std::vector<char> > grid = {};
	std::set<std::string> expect = {};
	EXPECT_EQ(expect, words_of_dict_in_grid(grid, dict));
}

void sameLetterTest() {
	std::vector<std::string> vec_of_str = { "car", "ccc", "cccccc", "meowcc" };
	Dictionary dict(vec_of_str);
	std::vector<std::vector<char> > grid;
	for (int i = 0; i < 3; i++) {
		grid.push_back({});
		for (int j = 0; j < 4; j++) {
			grid[i].push_back('c');
		}
	}
	std::set<std::string> expect = { "ccc", "cccccc" };
	EXPECT_EQ(expect, words_of_dict_in_grid(grid, dict));
}

void jaggetGridTest() {
	std::vector<std::string> vec_of_str = { "car", "ccc", "cccccc", "meowcc" };
	Dictionary dict(vec_of_str);
	std::vector<std::vector<char> > grid = { { 'a', 'b', 'c', 'd' },{ 'a', 'b' },{ 'a', 'b', 'c', 'd', 'e' } };
	std::set<std::string> expect = {};
	EXPECT_EQ(expect, words_of_dict_in_grid(grid, dict));
}

void tests() {
	dictionaryTest();
	simpleTest();
	emptyDictionaryTest();
	emptyGridTest();
	sameLetterTest();
	jaggetGridTest();
}

int main() {
	tests();
	system("pause");
}
