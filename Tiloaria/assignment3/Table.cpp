#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

/*Dictionary - can find words or his prefics contained inside.*/
struct Dictionary {
	Set<string> dict, pref;
	Dictionary (vector<sting> dict) {
		for (int cur_el : dict) {
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

/*Check if the way is the word from the Dictionary*/
bool rec_find_of_words(set<string> &contains, Matrix& cur_mat, bool[][] &visited, int wi, int he) {
	if (wi < 0 || wi > )
	int add[8][2];//array to go to the next letter in grid
	add[0][0] = -1; add[0][1] = -1;
	add[1][0] = -1; add[1][1] = 0;
	add[2][0] = -1; add[2][1] = 1;
	add[3][0] = 0; add[3][1] = 1;
	add[4][0] = 1; add[4][1] = 1;
	add[5][0] = 1; add[5][1] = 0;
	add[6][0] = 1; add[6][1] = -1;
	add[7][0] = 0; add[7][0] = -1;
}

struct Word_matrix {
	int width = 0, height = 0;
	vector<vector<char> > grid;
	Word_matrix (vector<vector<char> > new_grid) {
		height = grid.size();
		if (height != 0)
			width = grid[0].size();
		grid = new_grid;
	}
	vector<string> find_all_words (Dictionary dict) {
		bool visited[width][height];
		set<string> contains;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				rec_find_of_words(contains, this, visited, i, j);
			}
		}
	}
};

int main () {
	return 0;
}
