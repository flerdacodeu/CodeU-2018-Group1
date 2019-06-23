#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

enum Mark {
	Unmarked,
	Permanent,
	Temporary
};

void dfs(char current,
	std::map<char, std::set<char>> &graph,
	std::map <char, Mark> &marks,
	std::vector <char> &path,
	bool &has_cycle) {

	if (marks[current] == Permanent) {
		return;
	}

	if (marks[current] == Temporary)
	{
		has_cycle = true;
		return;
	}

	marks[current] = Temporary;

	for (const auto& v : graph[current]) {
		dfs(v, graph, marks, path, has_cycle);
	}

	marks[current] = Permanent;

	path.push_back(current);
}

bool top_sort(std::map <char, std::set<char>> &graph, std::vector <char> &alphabet) {
	std::map <char, Mark> marks;
	bool has_cycle = false;

	for (auto& v : graph) {
		if (marks[v.first] == Unmarked) {
			dfs(v.first, graph, marks, alphabet, has_cycle);
		}
	}

	std::reverse(alphabet.begin(), alphabet.end());
	return has_cycle;
}


std::map<char, std::set<char>> build_graph(const std::vector<std::string>& dictionary) {
	std::map<char, std::set<char>> graph;

	for (size_t i = 0; i < dictionary.size(); ++i) {
		for (size_t j = i + 1; j < dictionary.size(); ++j) {
			
			size_t length = std::min(dictionary[i].size(), dictionary[j].size());
			
			for (size_t k = 0; k < length; ++k) {
				if (dictionary[i][k] != dictionary[j][k]) {
					graph[dictionary[i][k]].insert(dictionary[j][k]);
					break;
				}
			}
		}
	}

	return graph;
}

void print_alphabet(std::vector<std::string> dictionary) {
	auto graph = build_graph(dictionary);

	std::vector <char> alphabet;
	bool has_cycle = top_sort(graph, alphabet);

	if (!has_cycle) {
		for (auto ch : alphabet)
			std::cout << ch << ' ';
	}
	else {
		std::cout << "No alphabet possible";
	}
}


int main() {
	std::vector<std::string> dictionary = { "ART", "RAT", "CAT", "CAR" };
	print_alphabet(dictionary);
}
