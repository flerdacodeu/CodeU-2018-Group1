#include <iostream>
#include <string>
using namespace std;

// case sensitive
int isAnagram(const string word1, string word2, bool sensitive) {
	if (word1.size() != word2.size())//checks if the words could be anagrams by the size of them
		return 0;
	int size1 = word1.size();
	int size2 = size1;
	string temp = word1;
	// checks if the letters"cover" each other
	for (int j = 0;j < size2;j++) {
		for (int k = 0;k < size1;k++) {
			if (temp.at(k) == word2.at(j)) {
				temp.erase(k, 1);
				word2.erase(j,1);
				k = size1;
				size1--;
			}
		}
	}
	if (word2.empty()) {
		return temp.empty();
		//if the temp string is empty and word2 is empty - it means we have "used" all the words 
		//which means the words are anagrams
	}
}
