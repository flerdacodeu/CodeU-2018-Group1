#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>

bool IsAnagram(std::string s1, std::string s2, bool is_case_sensitive) {
	std::vector<char> s1_chars;
	std::vector<char> s2_chars;

	if (s1.size() != s2.size())
		return false;

	if (is_case_sensitive) {
		s1_chars.push_back(s1[i]);
		s2_chars.push_back(s2[i]);
	}
	else {
		s1_chars.push_back(tolower(s1[i]));
		s2_chars.push_back(tolower(s2[i]));
	}

	std::sort(s1_chars.begin(), s1_chars.end());
	std::sort(s2_chars.begin(), s2_chars.end());

	return s1_chars == s2_chars;
}
std::vector<std::string> SplitByWords(const std::string& sentence) {
	int index_start = 0, index_end = 0;
	vector<std::string> sentence_words;
	for (int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == ' ' || i == sentence.size() - 1) {
			index_end = i;
			string str = sentence.substr(index_start, index_end - index_start + 1);
			std::sort(str.begin(), str.end());
			sentence_words.push_back(str);
			index_start = index_end + 1;
		}
	}
	return sentence_words;
}
bool IsSentenceAnagram (std::string sent1, std::string sent2, bool is_case_sensitive) {
	std::vector <std::string> sent1_words = splitByWords(sent1);
	std::vector <std::string> sent2_words = splitByWords(sent2);
	
	if (sent1_words.size() != sent2_words.size())
		return false;
	
	std::sort(sent1_words.begin(), sent1_words.end());
	std::sort(sent2_words.begin(), sent2_words.end());
	
	for (int i = 0; i < sent1_words.size(); i++) 
		if (!IsAnagram(sent1_words[i], sent2_words[i], is_case_sensitive))
			return false;
	return true;
}
