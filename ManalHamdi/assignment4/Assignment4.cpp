#include <iostream>
#include <utility>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

bool isValidNeighbour(const std::vector<std::vector<bool>> &map_tiles, int row, int column) {
	unsigned number_rows = map_tiles.size();
	unsigned number_columns = map_tiles[0].size();
	return (map_tiles[row][column] && row >= 0 && row < number_rows && column >= 0 && column < number_columns);
}
std::vector<std::pair<int, int>> getNeighboursIndices(
					const std::vector<std::vector<bool>> &map_tiles, 
					int row, int column) {
	std::vector<std::pair<int, int>> neighbours;
	
	int delta_rows[] = {1, -1, 0, 0};
	int delta_cols[] = {0, 0, 1, -1};
	
	for (int i = 0; i < 4; i++) {
		if (isValidNeighbour(row + delta_rows[i], column + delta_cols[i])) {
			neighbours.push_back(std::make_pair(row + delta_rows[i], column + delta_cols[i]));
		}
	}
	return neighbours;
}
bool isInputCorrect(const std::vector<std::vector<bool>> &map_tiles) {
	if (map_tiles.empty())
		return false;
	unsigned number_columns = (unsigned)map_tiles[0].size();
	for (int i = 0; i < map_tiles.size(); i++) {
		if (map_tiles[i].size() != number_columns) {
			return false;
		}
	}
	return true;
}
void BFS(const std::vector<std::vector<bool>> &map_tiles, 
	 int start_row,  int start_column, 
	 std::vector<std::vector<bool>> &visited) {
	std::queue <std::pair<int, int>> q;
	
	q.push(std::make_pair(start_row, start_column));
	while (!q.empty()) {
		auto current = q.front();
		q.pop();
		if (visited[current.first][current.second]) {
			continue;
		}
		visited[current.first][current.second] = true;

		auto neighbours = 
			getNeighboursIndices(map_tiles, current.first, current.second);
		for (auto neighbour: neighbours) {
			q.push(neighbour);
		}
	}
}
int countNumberIslands(const std::vector<std::vector<bool>> &map_tiles) {
	if (!isInputCorrect(map_tiles)) {
		return;
	}
	unsigned number_rows = map_tiles.size();
	unsigned number_columns = map_tiles[0].size();
	
	int count_islands = 0;
	std::vector<std::vector<bool>> visited(number_rows, std::vector<bool>(number_columns, false));
	for(int i = 0; i < number_rows; i++) {
		for(int j = 0; j < number_columns; j++) {
			if (!map_tiles[i][j] || visited[i][j]) {
				continue;
			}
			BFS(map_tiles, i, j, visited);
			count_islands++;
		}
	}
	return count_islands;
} 
void testEmptyMapTiles() {
	std::vector<std::vector<bool>> map_tiles;
	EXPECT_EQ(0, countNumberIslands(map_tiles, 0, 0));
}
void testOneCellMapTiles() {
	std::vector<std::vector<bool>> map_tiles = {{true}};
	EXPECT_EQ(1, countNumberIslands(map_tiles, 1, 1));	
}
void testPositiveMapTiles() {
	std::vector<std::vector<bool>> map_tiles = 
		{{false, true, false, true}, 
		 {true, true,false, false}, 
		 {false, false,true, false}, 
		 {false, false,true, false}};
	EXPECT_EQ(3, countNumberIslands(map_tiles, 4, 4));	
}
void testNoIslandsMapTiles() {
	std::vector<std::vector<bool>>  map_tiles = {{false, false}, {false, false}};
	EXPECT_EQ(0, countNumberIslands(map_tiles, 2, 2));	
}

int main(void) {
	testEmptyMapTiles();
	testOneCellMapTiles();
	testPositiveMapTiles();
	testNoIslandsMapTiles();
	
	return 0;
}
