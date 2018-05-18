#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;

bool isAnagramCaseSensitive(string s1, string s2) {
	if (s1.size() != s2.size())
		return false;

	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] != s2[i])
			return false;
	}
	return true;
}
bool isAnagramCaseInsensitive(string s1, string s2) {
	if (s1.size() != s2.size())
		return false;
	for (int i = 0; i < s1.size(); i++) {
		s1[i] = tolower(s1[i]);
		s2[i] = tolower(s2[i]);
	}
	return isAnagramCaseSensitive(s1, s2);
}
bool isSentenceAnagram (string sent1, string sent2) {
	vector <string> vSent1, vSent2;
	if (sent1.size() != sent2.size())
		return false;
	int index_start = 0, index_end = 0;
	for (int i = 0; i < sent1.size(); i++) {
		if (sent1[i] == ' ' || i == sent1.size() - 1) {
			index_end = i;
			string str = sent1.substr(index_start, index_end - index_start + 1);
			sort(str.begin(), str.end());
			vSent1.push_back(str);
			index_start = index_end + 1;
		}
	}
	for (int i = 0; i < sent2.size(); i++) {
		if (sent2[i] == ' ' || i == sent2.size() - 1) {
			index_end = i;
			string str = sent2.substr(index_start, index_end - index_start + 1);
			sort(str.begin(), str.end());
			vSent2.push_back(str);
			index_start = index_end + 1;
		}
	}

	sort(vSent1.begin(), vSent1.end());
	sort(vSent2.begin(), vSent2.end());
	for (int i = 0; i < vSent1.size(); i++) 
		if (!isAnagramCaseSensitive(vSent1[i],vSent2[i]))
			return false;
	return true;

}
