#include <iostream>
#include <string>
using namespace std;

// case sensitive
int isAnagram(const string word1, string word2) {
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
int main() {
	//test1
	bool test1 = isAnagram("Silent", "listen");
	cout << test1;
	//test2
	bool test2 = isAnagram("what", "thaw");
	cout << test2;
	//test3
	bool test3 = isAnagram("car", "arc");
	cout << test3;
	//test4
	bool test4 = isAnagram(" ", "");
	cout << test4;
	//test5
	bool test5 = isAnagram("dusty", "studySS");
	cout << test5;
	//test5
	bool test6 = isAnagram("BanaNa", "BaNana");
	cout << test6;
	//test7
	bool test7 = isAnagram("", "");
	cout << test7;
	cin >> test1;
}
