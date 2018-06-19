//Assumption1: the function should be case insensitive because in real world
#include <iostream>
#include <map>
#include <string>
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
		bool isPrefix(const std::string big, const std::string small) {
			if (big.size() >= small.size()) {
				return big.substr(0, small.size()) == small;
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
public:
	std::vector<std::vector<char>> grid;
	int number_rows, number_columns;
};
bool valid_index(int row, int column, int grid_number_rows, int grid_number_columns) {
	if (row >= 0 && row < grid_number_rows && column >= 0 && column < grid_number_columns)
		return true;
	else
		return false;
}
std::vector<pair<int,int> > getNeighboorIndices(int current_index_row, int current_index_column, int grid_number_rows, int grid_number_columns) {
	std::vector<std::pair<int,int>> neighboors_indeces;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (valid_index(current_row + i, current_column + j, grid_number_rows, grid_number_columns)) {
				neighboors_indeces.push_back(current_row + i, current_column + j);
			}
   		}
	}
	return neighboors_indeces;
}
void DFS(Dictionary &dictionary,Grid &grid, std::vector<std::string> &words_found, int current_index_row, int current_index_column, std::string &word, std::vector<std::vector<bool> > &visited) {
	if(visited[current_index_row][current_index_column])
		return;
	visited[current_index_row][current_index_column] = true;
	word.push_back(grid[current_index_row][current_index_column]);
	if (dictionary.isPrefix(word)) {
		if (dictionary.isWord(word))
			words_found.push_back(word);
	}
	else {
		return;
	}
	std::vector<pair<int,int>> neighboors_indeces = getNeighboorIndices(current_index_row, current_index_column, grid.number_rows, grid.number_columns);
	for (auto neighboor: neighboors_indeces) {
		return DFS(dictionary, grid, neighboor.first, neighboor.second);
	}
	visited[current_row][current_column] = false;
	word.pop_back();
}

std::vector<std::string> findAllWordsInGrid(Dictionary &dictionary, Grid &grid) {
	std::vector<std::string> words_grid;
	std::string word;
	std::vector<std::vector<bool> > visited(grid.number_rows, vector<bool>(grid.number_columns, false));

	for (int i = 0; i < dictionary.number_rows; i++) {
		for (int j = 0; j < dictionary.number_columns; j++) {
			DFS(dictionary, grid, words_grid, grid[i][j],i,j, word, visited);
		}
	}
	return words_grid;
}