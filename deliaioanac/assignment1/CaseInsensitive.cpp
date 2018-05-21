#include <string>
#include <vector>
#include <algorithm>

#define ALPHA_LEN 26

using namespace std;

bool verifyAnagram(string initial, string anagram) {
    // If the words have different sizes, they can't
    // be anagrams
    if (anagram.size() != initial.size()) {
        return false;
    }

    // Since the algorithm is case insensitive, we lower
    // the words so that we only have lowercase chars
    transform(initial.begin(), initial.end(), initial.begin(), ::tolower);
    transform(anagram.begin(), anagram.end(), anagram.begin(), ::tolower);

    // Keeps count of the frequency of each letter
    // in the initial word
    vector<int> frequencies(ALPHA_LEN);

    for (char c : initial) {
        frequencies[c - 'a'] ++;
    }

    // Check if the letters appear with the same
    // frequencies in the supposed anagram
    for (char c : anagram) {
        if (frequencies[c - 'a'] == 0) {
            return false;
        }

        frequencies[c - 'a'] --;
    }

    return true;
}
