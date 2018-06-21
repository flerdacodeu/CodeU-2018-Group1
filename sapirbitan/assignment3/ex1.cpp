#include <iostream>
#include <string>
#include <vector>

using namespace std;

//this class contains the row and the column of the cell
class cell {
public:
	int row;
	int column;
};


//the best way to implement a Dictionary class is to have a "dictionary" - the words in the dictionary
//and the number of words in the Dictionary
class Dictionary {
	private:
		string * my_dictionary;
		int num_of_words = 0;
	public:
		Dictionary();
		Dictionary(int num_of_w);
		int getNumOfWords();
		string* getDictionary();
		bool isWord(string word);
		bool isPrefix(string pre);
		void print();
		void addWord(string word);
};
//constructor
Dictionary::Dictionary(int num_of_w) {
	num_of_words = num_of_w;
	my_dictionary = new string[num_of_words];
}
//default constructor
Dictionary::Dictionary() {
	cout << "how many words are in the Dictionary?" << endl;
	cin >> num_of_words;
	cout << "Please enter the words of your dictionary" << endl;
	my_dictionary = new string[num_of_words];
	for (int i = 0; i < num_of_words;i++)
		cin >> my_dictionary[i];
}

int Dictionary::getNumOfWords() {
	return num_of_words;
}

string* Dictionary::getDictionary() {
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
	string* temp_dictionary = new string[num_of_words];
	for (int i = 0; i < num_of_words-1;i++)
		temp_dictionary[i] =my_dictionary[i];
	temp_dictionary[num_of_words - 1] = word;
	for (int i = 0; i < num_of_words;i++)
		my_dictionary[i] = temp_dictionary[i];
}

//checks if one of the adjacent cells is unvalid
bool goodRowColumn(int row, int column, int num_of_rows, int num_of_columns) {
	if (row >= 0 && row < num_of_rows && column >= 0 && column < num_of_columns)
		return true;
	else
		return false;
}
//finds all of the adjacent cells
vector<cell> getNeighbors(int current_row, int current_column, int num_of_rows, int num_of_columns) {
	vector<cell> neighbors;
	cell temp_cell;
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
void checkCurrentCell(Dictionary &my_dictionary, vector<vector<char>> &grid, vector<string> &temp_dict, int current_row, int current_column, string word, vector<vector<bool>> &been_there) {
	//we're not allowed to repeat the same cell, so if we've already been to this cell...
	if (been_there[current_row][current_column])
		return;
	word.push_back(grid[current_row][current_column]);
	if (my_dictionary.isPrefix(word)) {
		been_there[current_row][current_column] = true;
		//if it's a prefix then we need this letter in the word - which means we've been in this cell
		if (my_dictionary.isWord(word)) {
			for (int j = 0;j < temp_dict.size();j++)
				if (temp_dict[j] == word)
					return;//in case the word can be found in various ways
			temp_dict.push_back(word);
		}
	}
	else {
		word.erase(word.size() - 1, 1);//if it's not a prefix we'd like to return to the word it was before
		return;
	}
	//find the cell's neighbors
	vector < cell > neighbors = getNeighbors(current_row, current_column, grid.size(), grid[0].size());
	for (int i = 0; i < neighbors.size();i++) {
		checkCurrentCell(my_dictionary, grid, temp_dict, neighbors[i].row, neighbors[i].column, word, been_there);
	}
}
vector<string> wordsFromGrid(Dictionary &my_dictionary, vector <vector<char>> &grid) {
	int row = grid.size();
	int column = grid[0].size();
	//in order to not go over the same cell
	int cell_counter = 0;
	int dict_counter = 0;
	vector<string> temp_dictionary;
	vector < vector<bool>> been_there;
	been_there.resize(row);
	for (int i = 0;i < row;i++) {
		been_there[i].resize(column);
		been_there[i].assign(column, 0);//initializing all of the cells to 0
	}
	for (int i = 0;i <row;i++) 
		for (int j = 0; j < column;j++){
			string word;//we'll have to initialize 'word' for every iteration
			checkCurrentCell(my_dictionary, grid, temp_dictionary, i, j, word, been_there);
			//after we're done with this cell we need to initialize all of the cells back to 0

			for (int K = 0;K < row;K++) 
				been_there[K].assign(column, 0);//initializing all of the cells to 0
		}
	
	return temp_dictionary;
}

vector<vector<char>> setGrid() {
	vector <vector <char>> grid;
	int rows, columns;
	//getting the number of rows and columns in the grid 
	cout << "How many rows are in the grid?" << endl;
	cin >> rows;
	cout << "How many columns are in the grid?" << endl;
	cin >> columns;
	grid.resize(rows);
	for (int i = 0; i < rows;i++)
		grid[i].resize(columns);
	//initializing the greed with input letters
	cout << "Enter the letters in the grid row by row(" <<rows*columns<<" letters):"<< endl;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns;j++) {
			cin >> grid[i][j];
		}
	//printing the grid
	cout << "This is your grid: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns;j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	return grid;
}

int main() {
	//creating grid
	vector<vector<char>> grid =setGrid();
	//creating dicionary
	Dictionary dict;
	
	//printing Dictionary
	cout << "This is your dictionary: " << endl;
	dict.print();
	
	vector<string> words;
	words = wordsFromGrid(dict, grid);
	cout << "The words we've found:" << endl;
	for(int i=0; i<words.size();i++)
		cout << words[i]<<endl;
	return 0;
}
