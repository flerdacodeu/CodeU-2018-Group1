#include <iostream>
#include <vector>
using namespace std;
//this class contains the row and the column of the cell
class Cell {
public:
	int row;
	int column;
};

bool goodRowColumn(int row, int column, int num_of_rows, int num_of_columns) {
	return (row >= 0 && row < num_of_rows && column >= 0 && column < num_of_columns);
}
//finds all of the adjacent cells
vector<Cell> getNeighbors(int current_row, int current_column, int num_of_rows, int num_of_columns) {
	vector<Cell> neighbors;
	Cell temp_cell;
	//top cell
	if (goodRowColumn(current_row -1, current_column, num_of_rows, num_of_columns)) {
		temp_cell.row = current_row -1;
		temp_cell.column = current_column;
		neighbors.push_back(temp_cell);
	}
	//bottum cell
	if (goodRowColumn(current_row +1, current_column, num_of_rows, num_of_columns)) {
		temp_cell.row = current_row + 1;
		temp_cell.column = current_column;
		neighbors.push_back(temp_cell);
	}
	//left cell
	if (goodRowColumn(current_row, current_column-1, num_of_rows, num_of_columns)) {
		temp_cell.row = current_row;
		temp_cell.column = current_column-1;
		neighbors.push_back(temp_cell);
	}
	//right cell
	if (goodRowColumn(current_row, current_column + 1, num_of_rows, num_of_columns)) {
		temp_cell.row = current_row;
		temp_cell.column = current_column + 1;
		neighbors.push_back(temp_cell);
	}
	return neighbors;//returns the valid adjacent cells
}
//checks if the island is bigger than one cell on the map
void checkArea(int row, int column, vector<vector<bool>> &map, vector<vector<bool>> &been_there) {
	if (!map[row][column])
		return;
	been_there[row][column] = true;//the only places we want to mark as been_there are the ones who are land
								  //in order to know it belongs to the same island
	vector<Cell> neighbors = getNeighbors(row, column,map.size(),map[0].size());
	for (int i = 0; i < neighbors.size();i++) {
		if(!(been_there[neighbors[i].row][neighbors[i].column]))
			checkArea(neighbors[i].row, neighbors[i].column, map, been_there);
	}
}
//finds out how many islands are there in the map
int findLand(int num_of_rows, int num_of_columns, vector<vector<bool>> map) {
	int num_of_islands = 0;
	vector < vector<bool>> been_there;
	been_there.resize(num_of_rows);
	for (int i = 0;i < num_of_rows;i++) {
		been_there[i].resize(num_of_columns);
		been_there[i].assign(num_of_columns, 0);//initializing all of the cells to 0
	}
	for (int i = 0; i < num_of_rows;i++) 
		for (int j = 0;j < num_of_columns;j++) {
			if (map[i][j]&&!been_there[i][j]) {
				checkArea(i, j, map, been_there);
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
	if (findLand(map1.size(), map1[0].size(), map1)!=3)
		cout<<"wrong output!"<<endl;
	//test 2
	vector<vector<bool>> map2 = { { true, false,true,false,true },
					{ true,false,false,true,false},
					{ false,true, true, false,true},
				     	{true, true, false, false,true},
					{true, true, false, true,false} };
	if (findLand(map2.size(), map2[0].size(), map2) != 7)
		cout << "wrong output!"<<endl;
	//test 3
	vector<vector<bool>> map3 = {{true},
								{false}};
	if (findLand(map3.size(), map3[0].size(), map3) != 1)
		cout << "wrong output!"<<endl;
	//test 4
	vector<vector<bool>> map4 = { { true, true,true,true,true },
					{ true,true,true,true,true } };
	if (findLand(map4.size(), map4[0].size(), map4) != 1)
		cout << "wrong output!" << endl;
	//test 5
	vector<vector<bool>> map5 = { { false,false,false,false },
					{ false,false,false,false },
					{ false, false,false,false } };
	if (findLand(map5.size(), map5[0].size(), map5) != 0)
		cout << "wrong output!" << endl;
}
int main() {

	tests();
	return 0;
}
