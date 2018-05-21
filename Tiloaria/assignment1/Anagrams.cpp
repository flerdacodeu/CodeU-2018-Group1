#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

bool is_anagrams(string s1, string s2) {
	int num_of_letters1[26] = {0}, num_of_letters2[26] = {0};//we think, that in anagrams are important only letters
	int len1 = s1.size();
	int len2 = s2.size();
	for (int i = 0; i < len1; i++) {
		if (s1[i] >= 'a' && s1[i] <= 'z') {
			num_of_letters1[s1[i] - 'a']++;
		} 
		else 
			if (s1[i] >= 'A' && s1[i] <= 'Z') {
				num_of_letters1[s1[i] - 'A']++;
			}
	}
	for (int i = 0; i < len2; i++) {
		if (s2[i] >= 'a' && s2[i] <= 'z') {
			num_of_letters2[s2[i] - 'a']++;
		}
		else
			if (s2[i] >= 'A' && s2[i] <= 'Z') {
				num_of_letters2[s2[i] - 'A']++;
			}
	}
	for (int i = 0; i < 26; i++) {
		if (num_of_letters1[i] != num_of_letters2[i]) {
			return false;
		}
	}
	return true;
}

int main () {
	if (is_anagrams("Apple", "apple"))
		cout << "Test 1 done\n";
	else
		cout << "Test 1 failed\n";
	if (is_anagrams("Good morning", "ornngim odog"))
		cout << "Test 2 done\n";
	else
		cout << "Test 2 failed\n";
	if (!is_anagrams("Ana", "Anna"))
		cout << "Test 3 done\n";
	else
		cout << "Test 3 failed\n";	
	return 0;
}
