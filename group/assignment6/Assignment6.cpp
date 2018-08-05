#include <iostream>
#include <set>
#include <vector>

struct Move {
    int car_moved, source_slot, destination_slot;
};


class ParkingLot {
private:
    static const int kEmptySpotValue = -1;

    std::vector<int> start_state, end_state, prohibited_cars;

    int FindEmptySlotIndex(const std::vector<int> &parking) {
        // TODO: Handle no empty slot.
        auto it = std::find(begin(parking), end(parking), kEmptySpotValue);
        return (int)std::distance(begin(parking), it);
    }
    std::vector<int> GetCarsInWrongPlace() {
        
    }
    std::vector<int> getCarsSafeToMove(const std::vector<int> &cars_in_wrong_order, const std::set<int> &prohibited_cars);

public:
    ParkingLot (starting_state, ending_state, prohibited_cars);
    std::vector<Move> getMoveSequence();

};
int findVacantSlot(const std::vector<int> &parking_lot) {
    for (int i = 0; i < parking_lot.size(); i++) {
        if (parking_lot[i] == -1) {
            return i;
        }
    }
    
    return -1;
}

std::vector<int> getCarsWrongPlace(const std::vector<int> &starting_state, const std::vector<int> &ending_state) {
    std::vector<int> cars_wrong_place;
    for (int i = 0; i < starting_state.size(); i++) {
        int current_car = starting_state[i];
        if (current_car != ending_state[i] && current_car != -1) {
            cars_wrong_place.push_back(current_car);
        }
    }
    return cars_wrong_place;
}

int findCarSlot(const std::vector<int> &parking_lot, int car) {
    for (int i = 0; i < parking_lot.size(); i++) {
        if (parking_lot[i] == car) {
            return i;
        }
    }
    return -1;
}

void deleteCarFromList(int car_to_delete, std::vector<int> &list_to_delete_from) {
    for (int i = 0; i < list_to_delete_from.size(); i++) {
        if (list_to_delete_from[i] == car_to_delete) {
            list_to_delete_from.erase(list_to_delete_from.begin() + i);
            return;
        }
    }
}

void addToMoveSequence(int car, int source, int destination, std::vector<Move> &move_sequence) {
    Move current_move;
    current_move.car_moved = car;
    current_move.source_slot = source;
    current_move.destination_slot = destination;
    move_sequence.push_back(current_move);
}

int moveCar(int car_to_move, int destination_slot, std::vector<int> &current_state) {
    int source_slot = findCarSlot(current_state, car_to_move);
    current_state[destination_slot] = car_to_move;
    return source_slot;
}

std::vector<int> getCarsSafeToMove(const std::vector<int> &cars_in_wrong_order, const std::set<int> &prohibited_cars) {
    std::vector<int> cars_safe_to_move;
    
    for (auto car: cars_in_wrong_order) {
        if (!prohibited_cars.count(car)) {
            cars_safe_to_move.push_back(car);
        }
    }

    return cars_safe_to_move;
}

std::vector<Move> getMoveSequence(std::vector<int> &starting_state, std::vector<int> &ending_state,
                                  std::vector<std::set<int>> prohibited) {
    
    std::vector<Move> move_sequence;
    
    if (starting_state.size() != ending_state.size()) {
        return move_sequence;
    }
    
    int ending_vacant_slot = findVacantSlot(ending_state);
    
    auto cars_wrong_place = getCarsWrongPlace(starting_state, ending_state);
    auto cars_safe_to_move = getCarsSafeToMove(cars_wrong_place, prohibited[ending_vacant_slot]);
    int current_vacant_slot = findVacantSlot(starting_state);
    
    while (cars_wrong_place.size() != 0) {
        int car_source_slot;
        int car_to_move;
        
        if (ending_state[current_vacant_slot] == -1) {
            if (cars_safe_to_move.size() == 0) {
                //error
                return std::vector<Move>();
            }
            car_to_move = cars_safe_to_move.back();
            cars_safe_to_move.pop_back();
        }
        else {
            car_to_move = ending_state[current_vacant_slot];
            deleteCarFromList(car_to_move, cars_wrong_place);
        }
        car_source_slot = moveCar(car_to_move, current_vacant_slot, starting_state);
        starting_state[car_source_slot] = -1;
        addToMoveSequence(car_to_move, car_source_slot, current_vacant_slot, move_sequence);
        current_vacant_slot = car_source_slot;
        
        deleteCarFromList(car_to_move, cars_safe_to_move);
        
    }
    return move_sequence;
}

void printPath(const std::vector<Move> &move_sequence) {
    for (auto move: move_sequence) {
        std::cout << "Car " << move.car_moved << " has been moved from "
        << move.source_slot << " to " << move.destination_slot << std::endl;
    }
}

int main() {
    //  simple test
    int parking_size = 4;
    std::vector<std::set<int>> prohibited = std::vector<std::set<int>>(parking_size - 1);
    std::vector<int> starting_state = {1, 2, -1, 3};
    std::vector<int> ending_state = {3, 1, 2, -1};
    
    auto move_sequence = getMoveSequence(starting_state, ending_state, prohibited);
    printPath(move_sequence);
    
    //  edge case
    parking_size = 4;
    starting_state = {1, 3, 2, -1};
    ending_state = {1, 2, 3, -1};
    move_sequence = getMoveSequence(starting_state, ending_state, prohibited);
    printPath(move_sequence);
    
    //  prohibited case
    parking_size = 4;
    starting_state = {1, 3, 2, -1};
    ending_state = {3, 2, 1, -1};
    prohibited = {
        {},
        {},
        {},
        {1, 2}
    };
    move_sequence = getMoveSequence(starting_state, ending_state, prohibited);
    printPath(move_sequence);

    
    starting_state = {1, -1, 2, 4, 3, 6, 9, 8, 7, 5};
    ending_state = {1, 2, 4, -1, 9, 8, 7, 5, 3, 6};
    move_sequence = getMoveSequence(starting_state, ending_state, prohibited);
    printPath(move_sequence);

}
