#include <iostream>
#include <string>
using namespace std;

// case sensitive
int isAnagram(const string& word1,const string& word2) {
	if ((word1.size() != word2.size())||k<0)//checks if the words are the same lenght
		return 0;
	int word1_size = word1.size();
	int word2_size = word1.size();
	string temp_word1 = word1;
	string changed_word2 = word2;

	for (int i = 0;i < word2_size;i++) {//runs over all the letters of the second word.
		for (int k = 0;k < word1_size;k++) {//runs over the letters of the first word
			//if there is a fit, erase the letters that 'fit' from the temporary words
			if (temp_word1.at(k) == word2.at(i)) {
				temp_word1.erase(k, 1);
				changed_word2.erase(0, 1);
				//we don't need to run over the rest of the words - since we've found a match,
				//plus - we don't want to delete any necessary letters(like test 8)
				k = word1_size;
				word1_size--;
			}
		}
	}
	return changed_word2.empty() && temp_word1.empty();
	//if the temp_word1 string is empty and word2 is empty - it means we have "used" all the words 
	//which means the words are anagrams
}

int main() {
	//test1
	cout << isAnagram("Silent", "listen") << endl;
	//test2
	cout << isAnagram("what", "thaw") << endl;
	//test3
	cout << isAnagram("car", "arc") << endl;
	//test4
	cout << isAnagram(" ", "") << endl;
	//test5
	cout << isAnagram("dusty", "studySS") << endl;
	//test6
	cout << isAnagram("BanaNa", "BaNana") << endl;
	//test7
	cout << isAnagram("", "") << endl;
	//test8
	cout << isAnagram("barn", "narbn") << endl;
}
