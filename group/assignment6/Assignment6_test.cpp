#include "Assignment6_test.h"
#include <time.h>
#include <algorithm>

using std::unordered_set;

using std::cerr;
using std::random_shuffle;

bool equals(vector<int> v1, vector<int> v2) {
	if (v1.size() != v2.size()) 
		return false;
	for (int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i])
                return false;
	}
       return true;
}

bool correct_actions_seq(vector<int> & start_seq, vector<int> & end_seq, vector<Move> actions) {
	vector<int> cur_seq = start_seq;
       for (int i = 0; i < actions.size(); i++) {
                int start_st = actions[i].source;
                int end_st = actions[i].destination;
                int num_of_car = actions[i].car;
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
        vector<Move> seq = {Move(2, 2, 1)};
	return correct_actions_seq(st, end, seq);
}

bool check_correctness(vector<int> start_seq, vector<int> end_seq, vector<Move> res) {
	if (!correct_actions_seq(start_seq, end_seq, res)) {
		cerr << "Solution isn't correct(\n";
		return false;
	}
        return true;
}

bool unit_test_1 () {
	vector<int> start_seq 	= {1, 2, -1, 4,  3};
	vector<int> end_seq 	= {1, 2,  3, 4, -1};
        vector<unordered_set<int>> prohibited = vector<unordered_set<int>>(start_seq.size());
        Solution sol = ParkingLot(start_seq, end_seq, prohibited).GetMoveSequence();
        if (!sol.has_solution)
            return false;
        vector<Move> res = sol.moves;
        if (!check_correctness(start_seq, end_seq, res))
                return false;
        if (res.size() != 1) {
		cerr << "Solution is correct, but number of actions isn't optimal\n";
	}
	return true;
}

bool unit_test_swap() {
	vector<int> start_seq 	= {1, 2, 4, 3, -1};
	vector<int> end_seq 	= {1, 2, 3, 4, -1};
        vector<unordered_set<int>> prohibited = vector<unordered_set<int>>(start_seq.size());
        Solution sol = ParkingLot(start_seq, end_seq, prohibited).GetMoveSequence();
        if (!sol.has_solution)
            return false;
        vector<Move> res = sol.moves;
	if (!check_correctness(start_seq, end_seq, res)) 
		return false;
	if (res.size() != 3) {
		cerr << "Solution is correct, but number of actions isn't optimal\n";
	}
	return true;
}

bool unit_test_easy_move() {
	vector<int> start_seq 	= {-1, 1, 2, 3, 4, -1, 5, 6,  7,  8};
	vector<int> end_seq 	= { 1, 2, 3, 4, 5,  6, 7, 8, -1, -1};

        vector<unordered_set<int>> prohibited = vector<unordered_set<int>>(start_seq.size());
        Solution sol = ParkingLot(start_seq, end_seq, prohibited).GetMoveSequence();
        if (!sol.has_solution) {
            cerr << "Program doesn't found exists solution\n";
            return false;
        }
        vector<Move> res = sol.moves;
        if (!check_correctness(start_seq, end_seq, res))
            return false;
	if (res.size() != 8) {
		cerr << "Solution is correct, but number of actions isn't optimal\n";
	}
	return true;
}

bool unit_test_mix() {
	vector<int> start_seq 	= { 4, 1, 2, 3,  7, -1, 5, 6, -1,  8};
	vector<int> end_seq 	= { 1, 2, 3, 4,  5,  6, 7, 8, -1, -1};
        vector<unordered_set<int>> prohibited = vector<unordered_set<int>>(start_seq.size());
        Solution sol = ParkingLot(start_seq, end_seq, prohibited).GetMoveSequence();
        if (!sol.has_solution)
            return false;
        vector<Move> res = sol.moves;
        if (!check_correctness(start_seq, end_seq, res))
		return false;
	if (res.size() != 10) {
		cerr << "Solution is correct, but number of actions isn't optimal\n";
	}
	return true;
}

void output_seq(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cerr << a[i] << " ";
}

bool random_tests() {
	srand(time(NULL));
	int num_of_tests = 10;
	vector<int> start_seq;
	vector<int> end_seq;
	int fale_tests = 0;
	for (int i = 0; i < num_of_tests; i++) {
		start_seq.clear();
		end_seq.clear();
		vector<int> help_seq;
		int seq_len = (rand() % 10) + 3;//length of sequence from 100 to 10100
		int num_of_cars = (rand() % seq_len);//number of cars from 0 to seq_len	
		for (int i = 1; i <= num_of_cars; i++) {
			help_seq.push_back(i);
		}
		for (int i = num_of_cars + 1; i <= seq_len; i++) {
			help_seq.push_back(-1);
		}
		random_shuffle(help_seq.begin(), help_seq.end());
		start_seq = help_seq;
		random_shuffle(help_seq.begin(), help_seq.end());
		end_seq = help_seq;
                vector<unordered_set<int>> prohibited = vector<unordered_set<int>>(start_seq.size());
                Solution sol = ParkingLot(start_seq, end_seq, prohibited).GetMoveSequence();
                if (!sol.has_solution)
                    return false;
                vector<Move> res = sol.moves;
                if (!check_correctness(start_seq, end_seq, res)) {
			cerr << "start sequence was:\n";
		       	output_seq(start_seq); 
			cerr << "\n";
			cerr << "end sequence was:\n";
			output_seq(end_seq);
		       	cerr << "\n";
        	        fale_tests++;
		}
	}
	if (fale_tests > 0) {
		cerr << fale_tests << "/" << num_of_tests << " was failed\n";
		return false;
	}
	return true;
}
