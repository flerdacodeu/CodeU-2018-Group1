#include "Assignment6_test.h"

using std::cerr;

bool equals(vector<int> v1, vector<int> v2) {
	if (v1.size() != v2.size()) 
		return false;
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i])
			return false;
	}
	return true;
}

bool correct_actions_seq(vector<int> & start_seq, vector<int> & end_seq, vector<AMove> actions) {
	vector<int> cur_seq = start_seq;
	for (int i = 0; i < actions.size(); i++) {
		int start_st = actions[i].get_start_car_state();
		int end_st = actions[i].get_end_car_state();
		int num_of_car = actions[i].get_number_of_car();

		if (start_st == -1) {
			cerr << "Sequens of action is incorect - start state in action " << i + 1 << " is free\n";
			return false;
		}
		if (num_of_car != cur_seq[start_st]) {
                        cerr << "Sequens of action is incorect - start state in action " << i + 1 
				<< " have another number of car. " << cur_seq[start_st] 
				<< " instead of " << num_of_car << " \n";
                        return false;
                }
		if (end_st == -1) {
                        cerr << "Sequens of action is incorect - end state in action " << i + 1 << " is free\n";
                        return false;
                }
		cur_seq[start_st] = -1; 
		cur_seq[end_st] = num_of_car;
	}
	return equals(cur_seq, end_seq);
}

bool unit_test_for_testing_test_function_action_seq() {//TODO remove after testing
	vector<int> st = {1, -1, 2};
	vector<int> end = {1, 2, -1};
	vector<AMove> seq = {AMove(2, 1, 2)};
	return correct_actions_seq(st, end, seq);
}

bool unit_test_1 () {
	vector<int> start_seq 	= {1, 2, 4, 3, -1};
	vector<int> end_seq 	= {1, 2, 3, 4, -1};
	vector<AMove> res = CarRearrangement(start_seq, end_seq).getMoves();
	if (!correct_actions_seq(start_seq, end_seq, res)) {
		cerr << "Solution isn't correct(\n";
		return false;
	}
	if (res.size() != 3) {
		cerr << "Solution is correct, but number of actions isn't optimal\n";
	}
	return true;
}
