#include <iostream>
#include <vector>
#include <set>
#include "Assignment6.h"

using std::vector;

// AMove  definition
AMove::AMove(int start_car_state, int end_car_state, int number_of_car) {
	this->start_car_state = start_car_state;
	this->end_car_state = end_car_state;
	this->number_of_car = number_of_car;
}

void AMove::write () {
	// TODO cout move
}

int AMove::get_start_car_state() {
	return start_car_state;
}

int AMove::get_end_car_state() {
	return end_car_state ;
}

int AMove::get_number_of_car() {
	return number_of_car;
}

// CarRearrangement definition
// Constructor, and method for getting the answer here.
CarRearrangement::CarRearrangement(vector<int> start_state, vector<int> end_state) {
	this->start_state = start_state;
	this->end_state = end_state;
}

vector<AMove> CarRearrangement::getMoves() {
	int empty_slot_number;
	for (int i = 0; i < start_state.size(); i++) {
		if (start_state[i] == -1) {
			empty_slot_number = i;
		}
	}
	// TODO Main Logic here.
	return vector<AMove>();
}

int findVacantSlot(const std::vector<int> &parking_lot)
{
	for (int i = 0; i < parking_lot.size(); i++) {
		if (parking_lot[i] == -1)
			return i;
	}
}

std::vector<int> getCarsWrongPlace(const std::vector<int> &starting_state, const std::vector<int> &ending_state)
{
	std::vector<int> cars_wrong_place;
	for (int i = 0; i < starting_state.size(); i++) {
		int current_state = starting_state[i];
		if (current_state != ending_state[i] && current_state != -1)
			cars_wrong_place.push_back(current_state);
	}
	return cars_wrong_place;
}

int findCarSlot(const std::vector<int> &parking_lot, int car)
{
	for (int i = 0; i < parking_lot.size(); i++) {
		if (parking_lot[i] == car)
			return i;
	}
}

void deleteCarFromList(int car_to_delete, std::vector<int> &list_to_delete_from)
{
	for (int i = 0; i < list_to_delete_from.size(); i++) {
		if (list_to_delete_from[i] == car_to_delete)
			list_to_delete_from.erase(list_to_delete_from.begin() + i);
	}
}

void addToMoveSequence(int car, int source, int destination, std::vector<std::vector<int>> &move_sequence)
{
	move_sequence[0].push_back(car);
	move_sequence[1].push_back(source);
	move_sequence[2].push_back(destination);
}

/*****************************************************************************
  - this function finds the path this parking lot is going through:
  it finds the vacant place in the parking lot and takes the car that's suppose
  to be there in the end.
  in case the parking space is vacant on both states(at the start and at the end)
  we'll just put a random car that is not in its right place in this spot
  - the function returns the path the cars have been through
 ******************************************************************************/
std::vector<std::vector<int>> changeParkingLot(std::vector<int> &starting_state, std::vector<int> &ending_state,
		std::vector<std::set<int>> prohibited)
{
	//  move_sequence is a table that says how we've transferred the cars on the parking lot
	//  move_sequence[0] - the car;
	//  move_sequence[1] - the source;
	//  move_sequence[2] - the destination;
	std::vector<std::vector<int>> move_sequence;
	if (starting_state.size() != ending_state.size())
		return move_sequence;
	move_sequence.resize(3);
	int vacant_slot = findVacantSlot(starting_state);
	std::vector<int> cars_wrong_place = getCarsWrongPlace(starting_state, ending_state);

	//  if the size of this vector is  0 - it means all of the cars are in the right place
	while (cars_wrong_place.size() != 0) {
		int car_source_slot;

		//      if the parking space is empty in both states we'll just take a car that is not in it's place
		//      and it is not prohibited to stay at vacant_slot
		if (ending_state[vacant_slot] == -1) {
			for (auto car : cars_wrong_place) {
				if (prohibited[vacant_slot].find(car) == prohibited[vacant_slot].end()) {
					car_source_slot = findCarSlot(starting_state, car);
					starting_state[vacant_slot] = car;
				}
			}
		} else {
			car_source_slot = findCarSlot(starting_state, ending_state[vacant_slot]);
			starting_state[vacant_slot] = ending_state[vacant_slot];

			//          delete the car from the list of the cars that are not in the right place
			deleteCarFromList(starting_state[vacant_slot], cars_wrong_place);
		}
		addToMoveSequence(starting_state[vacant_slot], car_source_slot, vacant_slot, move_sequence);
		starting_state[car_source_slot] = -1;
		vacant_slot = car_source_slot;

	}
	return move_sequence;
}

//prints the car's path
void printPath(std::vector<std::vector<int>> move_sequence)
{
	//  for every change in the parking lot
	if (move_sequence.size() != 0)
		for (int i = 0; i < move_sequence[0].size(); i++) {
			std::cout << "move car #" << move_sequence[0][i]
				<< " from space " << move_sequence[1][i]
				<< " to " << move_sequence[2][i]
				<< std::endl;
		}
	std::cout << std::endl;
}

//main function
	void
getMoveSequence(std::vector<int> &starting_state, std::vector<int> &ending_state, std::vector<std::set<int>> prohibited)
{
	std::vector<std::vector<int>> move_sequence;
	move_sequence = changeParkingLot(starting_state, ending_state, prohibited);
	printPath(move_sequence);
}

int inside_test()
{
	//  simple test
	int parking_size = 4;
	std::vector<std::set<int>> prohibited = std::vector<std::set<int>>(parking_size);
	std::vector<int> a = {1, 2, -1, 3};
	std::vector<int> b = {3, 1, 2, -1};
	getMoveSequence(a, b, prohibited);

	//  edge case
	parking_size = 4;
	a = {1, 3, 2, -1};
	b = {1, 2, 3, -1};
	getMoveSequence(a, b, prohibited);

	//  prohibited case
	parking_size = 4;
	a = {1, 3, 2, -1};
	b = {3, 2, 1, -1};
	prohibited = {
		{},
		{},
		{},
		{1, 2}
	};
	getMoveSequence(a, b, prohibited);

	a = {1, -1, 2, 4, 3, 6, 9, 8, 7, 5};
	b = {1, 2, 4, -1, 9, 8, 7, 5, 3, 6};
	getMoveSequence(a, b, prohibited);
}
