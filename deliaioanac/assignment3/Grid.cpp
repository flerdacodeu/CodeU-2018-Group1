#include "Dictionary.cpp"
#include <unordered_set>

namespace {
    const int NUMBER_OF_DIRECTIONS = 8;
}

class Grid {
    private:
        std::vector<std::vector<char> > grid_;
        // Difference that must be added to current coordinates to obtain
        // the 8 possible directions to go to.
        int iDiff_[NUMBER_OF_DIRECTIONS] = {0, 0, 1, -1, -1, -1, 1, 1};
        int jDiff_[NUMBER_OF_DIRECTIONS] = {-1, 1, 0, 0, 1, -1, 1, -1};

        // Check whether grid coordinates are in bounds.
        bool isInBounds(int i, int j) {
            return i >= 0 && j >= 0 && i < grid_.size() && j < grid_[i].size();
        }

        void backtrack(const std::unique_ptr<Trie> &dict, std::unordered_set<std::string> &solution,
                std::vector<std::vector<bool> > &visited, int i, int j, std::string &word) {
            // Add current letter of the grid to the word and mark it as already visited,
            // so it won't be used twice in the same word.
            word.push_back(grid_[i][j]);
            visited[i][j] = true;

            // If the current succession of letters in not a prefix,
            // it can't be a word, so return.
            if (!dict->isPrefix(word)) {
                visited[i][j] = false;
                word.pop_back();
                return;
            }

            // If the current succesion of letters is a word, add it to the list.
            if (dict->isWord(word)) {
                solution.insert(word);
            }

            // Continue to search in the grid on all possible directions, as words can also be
            // extended by other words.
            for (int k = 0; k < NUMBER_OF_DIRECTIONS; k ++) {
                if (isInBounds(i + iDiff_[k], j + jDiff_[k]) && !visited[i + iDiff_[k]][j + jDiff_[k]]) {
                    backtrack(dict, solution, visited, i + iDiff_[k], j + jDiff_[k], word);
                }
            }

            visited[i][j] = false;
            word.pop_back();
        }

    public:
        Grid(const std::vector<std::vector<char> > &newGrid) {
            grid_ = newGrid;
        }

        std::vector<std::string> wordSearch(const std::unique_ptr<Trie> &dict) {
            // If the grid is empty, not word from the dictionary can be found.
            if (grid_.empty()) {
                return std::vector<std::string>();
            }

            std::unordered_set<std::string> solution;
            std::vector<std::vector<bool> > visited;

            for (int i = 0; i < grid_.size(); i ++) {
                visited.push_back(std::vector<bool>(grid_[i].size(), false));
            }

            std::string word = "";

            // Start from every cell of the grid and see all the words that can be formed starting there.
            // Use an unordered_set for storing, to avoid duplicates.
            for (int i = 0; i < grid_.size(); i ++) {
                for (int j = 0; j < grid_[i].size(); j ++) {
                    backtrack(dict, solution, visited, i, j, word);
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
