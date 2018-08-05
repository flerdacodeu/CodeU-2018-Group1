#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Move {
  int car, source, destination;
  
  Move(int car, int source, int destination) {
    this->car = car;
    this->source = source;
    this->destination = destination;
  }
};

class ParkingLot {
private:
  const int kEmptySpotValue = -1;
  
  std::vector<int> start_state, end_state;
  std::vector<std::set<int>> prohibited_cars;
  
  std::map<int,int> MapCarsToIndices() {
    std::map<int,int> index_of_car;
    for (int i = 0; i < start_state.size(); i++) {
      if (!isEmptySlot(start_state[i])) {
        index_of_car[start_state[i]] = i;
      }
    }
    return index_of_car;
  }
  
  int FindEmptySlotIndex(const std::vector<int> &parking) {
    // TODO: Handle no empty slot.
    auto it = std::find(begin(parking), end(parking), kEmptySpotValue);
    return (int)std::distance(begin(parking), it);
  }
  
  bool isEmptySlot(int car) {
    return car == kEmptySpotValue;
  }
  
  std::set<int> GetCarsInWrongPlace() {
    std::set<int> cars_in_wrong_place;
    for (int i = 0; i < start_state.size(); i++) {
      if (start_state[i] != end_state[i] && !isEmptySlot(start_state[i])) {
        cars_in_wrong_place.insert(start_state[i]);
      }
    }
    return cars_in_wrong_place;
  }
  
  std::set<int> GetCarsSafeToMove(const std::set<int> &cars_in_wrong_order,
                                  const std::set<int> &prohibited_cars) {
    std::set<int> cars_safe_to_move;
    for (auto car: cars_in_wrong_order) {
      if (!prohibited_cars.count(car)) {
        cars_safe_to_move.insert(car);
      }
    }
    return cars_safe_to_move;
  }
  
public:
  ParkingLot (std::vector<int> start_state, std::vector<int> end_state,
              std::vector<std::set<int>> prohibited_cars) {
    this->start_state = start_state;
    this->end_state = end_state;
    this->prohibited_cars = prohibited_cars;
  }
  
  std::vector<Move> getMoveSequence() {
    if (start_state.size() != end_state.size()) {
      // TODO: ERROR HANDLING.
      return {};
    }
    
    int end_empty_slot = FindEmptySlotIndex(end_state);
    
    auto cars_in_wrong_place = GetCarsInWrongPlace();
    auto cars_safe_to_move = GetCarsSafeToMove(cars_in_wrong_place, prohibited_cars[end_empty_slot]);
    auto index_of_car = MapCarsToIndices();
    int current_empty_slot = FindEmptySlotIndex(start_state);
    
    std::vector<Move> move_sequence;
    auto RecordMove = [&](int car, int src, int dest) {
      move_sequence.push_back(Move(car, src, dest));
    };
    
    while (!cars_in_wrong_place.empty()) {
      int car_to_move;
      if (end_state[current_empty_slot] == -1) {
        if (cars_safe_to_move.empty()) {
          // TODO: ERROR HANDLING.
          return std::vector<Move>();
        }
        car_to_move = *cars_safe_to_move.begin();
      }
      else {
        car_to_move = end_state[current_empty_slot];
        cars_in_wrong_place.erase(car_to_move);
      }
      
      RecordMove(car_to_move, index_of_car[car_to_move], current_empty_slot);
      std::swap(index_of_car[car_to_move], current_empty_slot);
      
      if (cars_safe_to_move.count(car_to_move)) {
        cars_safe_to_move.erase(car_to_move);
      }
    }
    
    return move_sequence;
  }
};

void printPath(const std::vector<Move> &move_sequence) {
  for (auto move: move_sequence) {
    std::cout << "Car " << move.car << " has been moved from "
    << move.source << " to " << move.destination << std::endl;
  }
}

int main() {
  //  simple test
  int parking_size = 4;
  std::vector<std::set<int>> prohibited =
      std::vector<std::set<int>>(parking_size - 1);
  std::vector<int> starting_state = {1, 2, -1, 3};
  std::vector<int> ending_state = {3, 1, 2, -1};
  
  auto move_sequence =
      ParkingLot(starting_state, ending_state, prohibited).getMoveSequence();
  
  printPath(move_sequence);
  
  return 0;
}
