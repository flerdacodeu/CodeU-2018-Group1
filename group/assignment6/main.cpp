#include "Assignment6_test.h"

using std::cerr;

int main () {
	if (!unit_test_for_testing_test_function_action_seq())
		cerr << "function from tests is incorrect\n";
	if (!unit_test_1())
		cerr << "unit_test_1 is incorrect\n";
	return 0;
}
