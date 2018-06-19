#include "Dictionary.cpp"
#include <unordered_set>

namespace {
    const int NUMBER_OF_DIRECTIONS = 8;
}

class Grid {
    private:
        std::vector<std::vector<char> > grid;
        // Difference that must be added to current coordinates to obtain
        // the 8 possible directions to go to.
        int iDiff[NUMBER_OF_DIRECTIONS] = {0, 0, 1, -1, -1, -1, 1, 1};
        int jDiff[NUMBER_OF_DIRECTIONS] = {-1, 1, 0, 0, 1, -1, 1, -1};

        // Check whether grid coordinates are in bounds.
        bool isInBounds(int i, int j) {
            return i >= 0 && j >= 0 && i < grid.size() && j < grid[0].size();
        }

        void backtrack(std::unique_ptr<Trie> &dict, std::unordered_set<std::string> &solution,
                std::vector<std::vector<bool> > visited, int i, int j, std::string word) {
            // Add current letter of the grid to the word and mark it as already visited,
            // so it won't be used twice in the same word.
            word.push_back(grid[i][j]);
            visited[i][j] = true;

            // If the current succession of letters in not a prefix,
            // it can't be a word, so return.
            if (!dict->isPrefix(word)) {
                return;
            }

            // If the current succesion of letters is a word, add it to the list.
            if (dict->isWord(word)) {
                solution.insert(word);
            }

            // Continue to search in the grid on all possible directions, as words can also be
            // extended by other words.
            for (int k = 0; k < NUMBER_OF_DIRECTIONS; k ++) {
                if (isInBounds(i + iDiff[k], j + jDiff[k]) && !visited[i + iDiff[k]][j + jDiff[k]]) {
                    backtrack(dict, solution, visited, i + iDiff[k], j + jDiff[k], word);
                }
            }
        }

    public:
        Grid(std::vector<std::vector<char> > &newGrid) {
            grid = newGrid;
        }

        std::vector<std::string> wordSearch(std::unique_ptr<Trie> &dict) {
            // If the grid is empty, not word from the dictionary can be found.
            if (grid.empty()) {
                return std::vector<std::string>();
            }

            std::unordered_set<std::string> solution;
            std::vector<std::vector<bool> > visited(grid.size(), std::vector<bool>(grid[0].size(), false));

            // Start from every cell of the grid and see all the words that can be formed starting there.
            // Use an unordered_set for storing, to avoid duplicates.
            for (int i = 0; i < grid.size(); i ++) {
                for (int j = 0; j < grid[0].size(); j ++) {
                    backtrack(dict, solution, visited, i, j, "");
                }
            }

            std::vector<std::string> elements;
            while (!solution.empty()) {
                elements.push_back(*solution.begin());
                solution.erase(*solution.begin());
            }

            return elements;
        }
};
