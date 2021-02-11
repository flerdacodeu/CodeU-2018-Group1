#include <iostream>
#include <string>
#include <vector>

using namespace std;

//this class contains the row and the column of the cell
class Cell {
public:
	int row;
	int column;
};


//the best way to implement a Dictionary class is to have a "dictionary" - the words in the dictionary
//and the number of words in the Dictionary
class Dictionary {
	private:
		vector<string> my_dictionary;
		int num_of_words = 0;
	public:
		Dictionary();
		Dictionary(int num_of_w, vector<string> words);
		int getNumOfWords();
		vector<string> getDictionary();
		bool isWord(string word);
		bool isPrefix(string pre);
		void print();
		void addWord(string word);
};
//default constractor
Dictionary::Dictionary() {
	num_of_words = 0;
}

//constructor
Dictionary::Dictionary(int num_of_w, vector<string> words) {
	num_of_words = num_of_w;
	for (int i=0;i < num_of_w;i++)
		my_dictionary.push_back(words[i]);
}

int Dictionary::getNumOfWords() {
	return num_of_words;
}

vector<string> Dictionary::getDictionary() {
	return my_dictionary;
}

//if "word" is equal to one of the words in the Dictionary - it's in the Dictionary
bool Dictionary::isWord(string word) {
	for (int i = 0;i < num_of_words;i++)
		if (word == my_dictionary[i])
			return 1;
	return 0;
}
//if the sub-string of a word in the Dictionary from 0 to the size of pre is equal to pre
//pre is a prefix of a word in the Dictionary
bool Dictionary::isPrefix(string pre) {
	int pre_size = pre.size();
	for (int i = 0;i < num_of_words;i++)
		if (my_dictionary[i].substr(0, pre_size) == pre)
			return 1;
	return 0;
	
}
//prints the dictionary word by word
void Dictionary::print() {
	for (int i = 0; i < num_of_words;i++)
		cout << my_dictionary[i] << endl;;
}
//thought II'd need this function but I've managed without it in the end - don't have the heart to erase it :( 
void Dictionary::addWord(string word) {
	num_of_words += 1;
	my_dictionary.push_back(word);
}

//checks if one of the adjacent cells is unvalid
bool goodRowColumn(int row, int column, int num_of_rows, int num_of_columns) {
	return (row >= 0 && row < num_of_rows && column >= 0 && column < num_of_columns);
}
//finds all of the adjacent cells
vector<Cell> getNeighbors(int current_row, int current_column, int num_of_rows, int num_of_columns) {
	vector<Cell> neighbors;
	Cell temp_cell;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {//all of the adjacent cells
			if (!(i == 0 && j == 0)) {//if we're not in the cell itself
				if (goodRowColumn(current_row + i, current_column + j, num_of_rows, num_of_columns)) {
					temp_cell.row = current_row + i;
					temp_cell.column = current_column + j;
					neighbors.push_back(temp_cell);
				}
			}
		}
	}
	return neighbors;//returns the valid adjacent cells
}
void checkCurrentCell(Dictionary &my_dictionary, vector<vector<char>> &grid, vector<string> &words_found, int current_row, int current_column, string word, vector<vector<bool>> &been_there) {
	//we're not allowed to repeat the same cell, so if we've already been to this cell...
	if (been_there[current_row][current_column])
		return;
	word.push_back(grid[current_row][current_column]);
	if (my_dictionary.isPrefix(word)) {
		//if it's not a prefix we haven't used this word  - we can use it later
		been_there[current_row][current_column] = true;
		//if it's a prefix then we need this letter in the word - which means we've been in this cell
		if (my_dictionary.isWord(word)) {
			for (int j = 0;j < words_found.size();j++)
				if (words_found[j] == word)
					return;//in case the word can be found in various ways
			words_found.push_back(word);
		}
	}
	else {
		word.pop_back();//if it's not a prefix we'd like to return to the word it was before
		return;
	}
	//find the cell's neighbors
	vector < Cell > neighbors = getNeighbors(current_row, current_column, grid.size(), grid[0].size());
	for (int i = 0; i < neighbors.size();i++) {
		checkCurrentCell(my_dictionary, grid, words_found, neighbors[i].row, neighbors[i].column, word, been_there);
	}
}
vector<string> wordsFromGrid(Dictionary &my_dictionary, vector <vector<char>> &grid) {
	int row = grid.size();
	int column = grid[0].size();
	vector<string> words_found;
	vector < vector<bool>> been_there;
	been_there.resize(row);
	for (int i = 0;i < row;i++) {
		been_there[i].resize(column);
		been_there[i].assign(column, 0);//initializing all of the cells to 0
	}
	for (int i = 0;i <row;i++) 
		for (int j = 0; j < column;j++){
			string word;//we'll have to initialize 'word' for every iteration
			checkCurrentCell(my_dictionary, grid, words_found, i, j, word, been_there);
			//after we're done with this cell we need to initialize all of the cells back to 0

			for (int K = 0;K < row;K++) 
				been_there[K].assign(column, 0);//initializing all of the cells to 0
		}
	
	return words_found;
}


void tests() {
	//test 1 -output should be: CAT,CAR,CARD
	vector<vector<char>> grid1 = { {'A', 'A','R'},
								{'T','C','D'} };
	Dictionary my_dict1;
	my_dict1.addWord("CAT");
	my_dict1.addWord("CART");
	my_dict1.addWord("CARD");
	my_dict1.addWord("CAR");
	vector<string> words;
	words = wordsFromGrid(my_dict1, grid1);
	cout << "output should be: CAT,CAR,CARD" << endl;
	for (int i = 0; i<words.size();i++)
		cout << words[i] << endl;
	//test 2 -output should be: CAR, CARR, CARRR,CAD
	vector<vector<char>> grid2 = { { 'A', 'A','R','R' },
								{ 'T','C','D','R' } };
	Dictionary my_dict2;
	my_dict2.addWord("CAR");
	my_dict2.addWord("CARR");
	my_dict2.addWord("CARRR");
	my_dict2.addWord("CART");
	my_dict2.addWord("CAD");
	my_dict2.addWord("CADC");
	words = wordsFromGrid(my_dict2, grid2);
	cout << "output should be: CAR, CARR, CARRR,CAD" << endl;
	for (int i = 0; i<words.size();i++)
		cout << words[i] << endl;
	//test 3 -output should be: HelLo, TaKI,HaT
	vector<vector<char>> grid3 = { { 'a', 'H','e','l' },
									{ 'T','K','o','L' },
									{'s', 'g','I','a'} };
	Dictionary my_dict3;
	my_dict3.addWord("HelLo");
	my_dict3.addWord("TaKI");
	my_dict3.addWord("HAT");
	my_dict3.addWord("HaT");
	my_dict3.addWord("soLo");
	my_dict3.addWord("Halo");
	words = wordsFromGrid(my_dict3, grid3);
	cout << "output should be: HelLo, TaKI,HaT" << endl;
	for (int i = 0; i<words.size();i++)
		cout << words[i] << endl;
	//test 4 -output should be: ROB, CAR,CARD
	//I've added this test to show you the reason I'm not adding to been_there unless it's a prefix
	//but maybe I'm wrong and I didn't understand what you've asked for - if I did - please let me know :)
	vector<vector<char>> grid4 = { { 'C', 'D','B' },
									{ 'A','R','O' } };
	Dictionary my_dict4;
	my_dict4.addWord("ROB");
	my_dict4.addWord("CARD");
	my_dict4.addWord("CAR");
	words = wordsFromGrid(my_dict4, grid4);
	cout << "output should be: ROB, CAR,CARD" << endl;
	for (int i = 0; i<words.size();i++)
		cout << words[i] << endl;

}



int main() {

	tests();
	return 0;
}
