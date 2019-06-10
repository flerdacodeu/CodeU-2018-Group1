#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

/*Dictionary - can find words or his prefics contained inside.*/
struct Dictionary {
	set<string> dict, pref;
	Dictionary (vector<string> new_dict) {
		for (string cur_el : new_dict) {
			dict.insert(cur_el);
			string cur_pref = "";
			for (int let = 0; let < cur_el.length(); let++) {
				cur_pref += cur_el[let];
				pref.insert(cur_pref);
			}	
		}
	}
	bool isWord(string s) {
		return (dict.find(s) != dict.end());
	}

	bool isPrefix(string s) {
		return (pref.find(s) != pref.end());
	}
};

struct Word_matrix;

void rec_find_of_words(set<string> &contains, Word_matrix &cur_mat, Dictionary &dict, vector<vector<bool> > &visited, int wi, int he, string cur_word);

struct Word_matrix {
	int width = 0, height = 0;
	vector<vector<char> > grid;
	Word_matrix (vector<vector<char> > new_grid) {
		height = new_grid.size();
		if (height != 0)
			width = new_grid[0].size();
		grid = new_grid;
	}
	vector<string> find_all_words (Dictionary dict) {
                vector<vector<bool>> visited(height);
		for (int i = 0; i < height; i++) {
			visited[i].resize(width, 0);
		}
		set<string> contains;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				visited[h][w] = true;
				rec_find_of_words(contains, *this, dict, visited, w, h, string(1, grid[h][w]));
				visited[h][w] = false;
			}
                }
		vector<string> ans;
		for (auto &it: contains) {
		 	ans.push_back(it);
		}
		return ans;
	}
};

/*Check if the way is the word from the Dictionary*/
void rec_find_of_words(set<string> &contains, Word_matrix &cur_mat, Dictionary &dict, vector<vector<bool> > &visited, int wi, int he, string cur_word) {
        if (!dict.isPrefix(cur_word))
		return;
	if (dict.isWord(cur_word))
		contains.insert(cur_word);
        int add[8][2];//array to go to the next letter in grid
	add[0][0] = -1; add[0][1] = -1;
	add[1][0] = -1; add[1][1] = 0;
	add[2][0] = -1; add[2][1] = 1;
	add[3][0] = 0; add[3][1] = 1;
	add[4][0] = 1; add[4][1] = 1;
	add[5][0] = 1; add[5][1] = 0;
	add[6][0] = 1; add[6][1] = -1;
	add[7][0] = 0; add[7][1] = -1;
	for (int i = 0; i < 8; i++) {
                int new_wi = wi + add[i][0];
		int new_he = he + add[i][1];
                if (new_wi < 0 || new_wi >= cur_mat.width)
			continue;
                if (new_he < 0 || new_he >= cur_mat.height)
			continue;
                if (visited[new_he][new_wi]) {
                        continue;
		}
                visited[new_he][new_wi] = true;
		rec_find_of_words(contains, cur_mat, dict, visited, new_wi, new_he, cur_word + cur_mat.grid[new_he][new_wi]);
		visited[new_he][new_wi] = false;
	}
        return;
}

bool eq_vectors(const vector<string> &v1, const vector<string> &v2) {
	set<string> s1(v1.begin(), v1.end());
	set<string> s2(v2.begin(), v2.end());
	return s1 == s2;
}

int main () {
	vector<vector<char>> table = {{'C', 'A', 'R'}, {'T', 'C', 'D'}};
	Word_matrix m(table);
        Dictionary dict({"CAR", "CARD", "CART", "CAT"});
        if (!eq_vectors(m.find_all_words(dict), {"CAR", "CARD", "CAT"}))
		cout << "Test 1 failed\n";
	return 0;
}
