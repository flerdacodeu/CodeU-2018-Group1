#include <iostream>
#include <vector>
using namespace std;
//this class contains the row and the column of the cell
class Cell {
public:
	int row;
	int column;
	Cell(int row, int column);
};

Cell::Cell(int i_row, int i_column) {
	row = i_row;
	column = i_column;
}
bool goodRowColumn(int row, int column, int num_of_rows, int num_of_columns) {
	return (row >= 0 && row < num_of_rows && column >= 0 && column < num_of_columns);
}



//finds all of the adjacent cells
vector<Cell> getNeighbors(int current_row, int current_column, int num_of_rows, int num_of_columns) {
	vector<Cell> neighbors;
	int count = 0;
	int j;
	int rows[] = { 0, 1, 0, -1 };
	int cols[] = { 1, 0, -1, 0 };
	for (int i : rows) {  // iterates over the rows
		j = cols[count];// iterates over the columns
		if (goodRowColumn(current_row + i, current_column + j, num_of_rows, num_of_columns)) { 
			neighbors.push_back(Cell(current_row + i, current_column + j));
		}
		 count++;
	}
	return neighbors;//returns the valid adjacent cells
}
//checks if the island is bigger than one cell on the map
void checkArea(int row, int column, int num_of_rows, int num_of_columns, const vector<vector<bool>> &map, vector<vector<bool>> &been_there) {
	if (!map[row][column])
		return;
	been_there[row][column] = true;//the only places we want to mark as been_there are the ones who are land
								  //in order to know it belongs to the same island
	vector<Cell> neighbors = getNeighbors(row, column,num_of_rows,num_of_columns);
	for (int i = 0; i < neighbors.size();i++) {
		if(!(been_there[neighbors[i].row][neighbors[i].column]))
			checkArea(neighbors[i].row, neighbors[i].column, num_of_rows, num_of_columns, map, been_there);
	}
}
//finds out how many islands are there in the map
int findLand(int num_of_rows, int num_of_columns,const vector<vector<bool>>& map) {
	int num_of_islands = 0;
	vector < vector<bool>> been_there(num_of_rows, vector<bool>(num_of_columns));
	for (int i = 0; i < num_of_rows;i++) 
		for (int j = 0;j < num_of_columns;j++) {
			if (map[i][j]&&!been_there[i][j]) {
				checkArea(i, j, num_of_rows, num_of_columns, map, been_there);
				num_of_islands += 1;
			}
		}
	return num_of_islands;
}

void tests() {
	//test 1
	vector<vector<bool>> map1 = { { false,true,false,true },
								{ true,true,false,false },
								{ false, false,true,false },
								{ false, false,true,false } };
	if (findLand(4, 4, map1)!=3)
		cout<<"wrong output! should print: 3, got: "<< findLand(4, 4, map1)<<endl;
	//test 2
	vector<vector<bool>> map2 = { { true, false,true,false,true },
								{ true,false,false,true,false},
								{ false,true, true, false,true},
								{true, true, false, false,true},
								{true, true, false, true,false} };
	if (findLand(5,5, map2) != 7)
		cout << "wrong output! should print: 7, got: " << findLand(5, 5, map2)<<endl;
	//test 3
	vector<vector<bool>> map3 = {{true},
								{false}};
	if (findLand(2, 1, map3) != 1)
		cout << "wrong output! should print: 1, got: " << findLand(2, 1, map3) <<endl;
	//test 4
	vector<vector<bool>> map4 = { { true, true,true,true,true },
	{ true,true,true,true,true } };
	if (findLand(2, 5, map4) != 1)
		cout << "wrong output! should print: 1, got: " << findLand(2, 5, map4) << endl;
	//test 5
	vector<vector<bool>> map5 = { { false,false,false,false },
								{ false,false,false,false },
								{ false, false,false,false } };
	if (findLand(3, 4, map5) != 0)
		cout << "wrong output! should print: 0, got: " << findLand(3, 4, map5) << endl;
}
int main() {

	tests();
	int i;
	cin >> i;
	return 0;
}
