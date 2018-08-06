#include "Assignment6_test.h"

using std::cerr;

int main () {
	if (!unit_test_for_testing_test_function_action_seq())
		cerr << "function from tests is incorrect\n";
	bool correct_unit_tests = true;
	if (!unit_test_1()) {
		cerr << "unit_test_1 is incorrect\n\n";
		correct_unit_tests = false;
	}
	if (!unit_test_swap()) {
		cerr << "unit_test_swap is incorrect\n\n"; 
		correct_unit_tests = false;
	}
	if (!unit_test_easy_move()) {
		cerr << "unit_test_easy_move is incorrect\n\n";
		correct_unit_tests = false;
	}
	if (!unit_test_mix()) {
		cerr << "unit_test_mix() is incorrect\n\n";
		correct_unit_tests = false;
	}
	if (correct_unit_tests) {
		if (!random_tests()) 
			cerr << "some of random tests are incorrect\n";
	}
	else
		cerr << "unit tests was have failed, random tests was skiped\n";
	return 0;
}
