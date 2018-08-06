#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using std::vector;

/*
 * Class for one iterate of moving
 **/
struct Move {
	int car, source, destination;
	Move(int car, int source, int destination);
};

struct Solution {
  bool has_solution;
  std::vector<Move> moves;
  
  Solution(bool has_solution, std::vector<Move> moves);
};


class ParkingLot {
private:
  const int kEmptySpotValue = -1;
  std::vector<int> start_state, end_state;
  std::vector<std::unordered_set<int>> prohibited_cars;
  std::unordered_map<int, int> MapCarsToIndices();
  int FindEmptySlotIndex(const std::vector<int> &parking);
  bool isEmptySlot(int car);
  std::unordered_set<int> GetCarsInWrongPlace();
  std::unordered_set<int> GetCarsSafeToMove();

public:
  ParkingLot (std::vector<int> start_state,
              std::vector<int> end_state,
              std::vector<std::unordered_set<int>> prohibited_cars);

  Solution GetMoveSequence();
};

