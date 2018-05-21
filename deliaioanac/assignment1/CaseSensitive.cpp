#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define ALPHA_LEN 26

bool verifyAnagram(bool caseSensitive, string initial, string anagram) {
    // If the words have different sizes, they can't
    // be anagrams
    if (anagram.size() != initial.size()) {
        return false;
    }

    // Check if the algorithm is case insensitive
    if (!caseSensitive) {
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

    // Case sensitive

    // Here, the ALPHA_LEN is double so the vector
    // can also count uppercase letters
    // (first ALPHA_LEN elements count lowercase,
    //  last ALPHA_LEN elements count uppercase)
    vector<int> frequencies(ALPHA_LEN  * 2);

    // Same algorithm as it was for case insensitive,
    // only taking into account the uppercase letters
    for (char c : initial) {
        if (c >= 'A' && c <= 'Z')
            frequencies[c - 'A' + ALPHA_LEN] ++;
        else
            frequencies[c - 'a'] ++;
    }

    for (char c : anagram) {
        if (c >= 'A' && c <= 'Z') {
            if (frequencies[c - 'A' + ALPHA_LEN] == 0) {
                return false;
            }

            frequencies[c - 'A' + ALPHA_LEN] --;
        } else {
            if (frequencies[c - 'a'] == 0) {
                return false;
            }

            frequencies[c - 'a'] --;
        }

    }

    return true;
}
