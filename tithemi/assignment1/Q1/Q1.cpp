#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char, int> count_characters(const std::string &s, bool is_case_sensitive = false) {
    std::unordered_map<char, int> characters;

    if (is_case_sensitive) {
        for (const char c : s) {
            characters[c] += 1;
        }
    } else {
        for (const char c : s) {
            characters[std::tolower(c)] += 1;
        }
    }

    return characters;
}

bool is_anagram(const std::string &a, const std::string &b, bool is_case_sensitive = false) {
    if (a.size() != b.size())
        return false;

    std::unordered_map<char, int> a_characters = count_characters(a, is_case_sensitive);
    std::unordered_map<char, int> b_characters = count_characters(b, is_case_sensitive);

    return a_characters == b_characters;
}

int main()
{
    std::cout << is_anagram("listen", "silent") << std::endl; // true 1
    std::cout << is_anagram("triangle", "integral") << std::endl; // true 1
    std::cout << is_anagram("apple", "pabble") << std::endl; // false 0
    std::cout << is_anagram("Listen", "silent", true) << std::endl; // false 0
    return 0;
}