#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

/*
 * Class for one iterate of moving
 **/
class AMove {
	private:
		int start_car_state, end_car_state, number_of_car;
	public:
		AMove(int start_car_state, int end_car_state, int number_of_car);
		
		void write(); 

		//get methods
		int get_start_car_state();

		int get_end_car_state();

		int get_number_of_car();
};

class CarRearrangement {
	private:
		vector<int> start_state, end_state;
		// Other convenient methods here (e.g: findEmptySlot)

	public:
		// Constructor, and method for getting the answer here.
		CarRearrangement(vector<int> start_state, vector<int> end_state);
		vector<AMove> getMoves();
};
