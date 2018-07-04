#include<cstdio>
#include<cstdlib>
#include<iostream>

using std::cout;
using std::string;

const int alphabetSize = 26;

int charToIndex(char ch) {
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';
    return ch - 'A';
}

bool is_anagram(const string& s1, const string& s2) {
        int num_of_letters1[alphabetSize] = {0}, num_of_letters2[alphabetSize] = {0};//we think, that in anagrams are important only letters
        for (char c : s1) {
            if (std::isalpha(c)) {
                num_of_letters1[charToIndex(c)]++;
            }
        }
        for (char c : s2) {
            if (std::isalpha(c)) {
                num_of_letters2[charToIndex(c)]++;
            }
	}
        for (int i = 0; i < alphabetSize; i++) {
                if (num_of_letters1[i] != num_of_letters2[i]) {
			return false;
		}
	}
	return true;
}

int main () {
        if (is_anagram("Apple", "apple"))
                cout << "Test 1 done\n";
	else
		cout << "Test 1 failed\n";
        if (is_anagram("Good morning", "ornngim odog"))
                cout << "Test 2 done\n";
	else
		cout << "Test 2 failed\n";
        if (!is_anagram("Ana", "Anna"))
                cout << "Test 3 done\n";
	else
                cout << "Test 3 failed\n";
	return 0;
}
