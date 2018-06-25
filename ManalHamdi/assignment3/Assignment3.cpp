#include <iostream>
#include <map>
#include <string>
#include <set>
#include <utility>
#include <vector>

class Dictionary {
	private:
		std::set<std::string> words;
	public:
		Dictionary(const std::vector<std::string> words) {
			for (auto word : words) {
				this->words.insert(word);
			}
		}
		bool isWord(const std::string word) {
			return words.count(word);
		}
		bool isPrefix(const std::string word, const std::string prefix) {
			if (word.size() >= prefix.size()) {
				return word.substr(0, prefix.size()) == prefix;
			}
			return false;
		}
		bool isPrefix(const std::string prefix) {
			for (auto word : words) {
				if (isPrefix(word, prefix)) {
					return true;
				}
			}
			return false;
		}
};
class Grid {
private: 
	int number_rows, number_columns;
public:
	std::vector<std::vector<char>> grid;
	Grid(const std::vector<std::vector<char>> grid) {
		this->grid = grid;
		number_rows = grid.size();
		if (number_rows != 0)
			number_columns = grid[0].size();
		else
			number_columns = 0;
	}
	void validateGrid(Grid &grid) {
		for (int i = 0; i < grid.number_rows; i++) {
			for (int j = 0; j < grid.number_columns; j++) {
				grid.grid[i][j] = tolower(grid.grid[i][j]);
			}
		}
	}
	bool validIndex(int row, int column) {
		return row >= 0 && row < number_rows && column >= 0 && column < number_columns;
	}
	std::vector<std::pair<int,int> > getNeighboorIndices(int current_index_row, int current_index_column) {
		std::vector<std::pair<int,int>> neighboors_indeces;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (validIndex(current_index_row + i, current_index_column + j)) {
					neighboors_indeces.push_back(std::make_pair(current_index_row + i, current_index_column + j));
				}
			}
		}
		return neighboors_indeces;
	}
};


void DFS(Dictionary &dictionary,Grid &grid, std::vector<std::string> &words_found, int current_index_row, int current_index_column, std::string &word, std::vector<std::vector<bool> > &visited) {
	if(visited[current_index_row][current_index_column]) {
		return;
	}
	visited[current_index_row][current_index_column] = true;
	word.push_back(grid.grid[current_index_row][current_index_column]);
	if (dictionary.isPrefix(word)) {
+		if (dictionary.isWord(word)) {
			words_found.push_back(word);
		}
	}
	else {
		return;
	}
	std::vector<std::pair<int,int>> neighboors_indeces = getNeighboorIndices(current_index_row, current_index_column);
	for (auto neighboor: neighboors_indeces) {
		return DFS(dictionary, grid, words_found, neighboor.first, neighboor.second, word, visited);
	}
	visited[current_index_row][current_index_column] = false;
	word.pop_back();
}

//Assumption: the function should be case insensitive because in real world "eat" and "EAT" stand for the same words
std::vector<std::string> findAllWordsInGrid(Dictionary &dictionary, Grid &grid) {
	std::vector<std::string> words_grid;
	std::string word;
	std::vector<std::vector<bool> > visited(grid.number_rows, std::vector<bool>(grid.number_columns, false));
	
	grid.validateGrid(grid);
	
	for (int i = 0; i < grid.number_rows; i++) {
		for (int j = 0; j < grid.number_columns; j++) {
			DFS(dictionary, grid, words_grid, grid.grid.[i][j],i,j, word, visited);
		}
	}
	return words_grid;
}
class Test {
private: std::vector<std::vector<char>> grid;
	Dictionary dictionary;
	Grid grid;
public:
	void testEmptyGrid() {
		grid = new Grid(std::vector<std::vector<char>>());
		dictionary = new Dictionary(std::set<std::string>{"caa", "notfound", "rdct"});
		EXPECT_EQ({},findAllWords(dictionary, grid));
	}
	void testEmptyDictionary() {
		grid = new Grid(std::vector<std::vector<char>>({{'a','a','r'},{'t','c','d'}}));
		dictionary = new Dictionary(std::set<std::string>());
		EXPECT_EQ({},findAllWords(dictionary, grid));
	}
	void testPositive() {
		grid = new Grid(std::vector<std::vector<char>>({{'a','a','r'},{'t','c','d'}}));
		dictionary = new Dictionary(std::set<std::string>{"caa", "notfound", "rdct"});
		EXPECT_EQ({“caa”, “rdct”},findAllWords(dictionary, grid));
	}
};
