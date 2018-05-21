#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <unordered_map>

//is_case_sensitive == 1 -  sensitive, is_case_sensitive == 0 - insensitive


void split_by_word(std::string &sentence, std::unordered_map<std::string, int> &word_counts, bool is_case_sensitive) {
    std::string cur;
    for (int i = 0; i <= sentence.length(); i++) {
        if (i == sentence.length() || !isalpha(sentence[i]) && !isdigit(sentence[i])) {
            if (!cur.empty()) {
                sort(cur.begin(), cur.end());
                word_counts[cur]++;
                cur = "";
            }
            if (i == sentence.length()) return;
        }
        else if (is_case_sensitive) cur += sentence[i];
        else cur += tolower(sentence[i]);
    }
}

bool is_anagram(std::string &sentence_a, std::string &sentence_b, bool is_case_sensitive) {
    std::unordered_map<std::string, int> word_counts_b;
    std::string cur;
    split_by_word(sentence_b, word_counts_b, is_case_sensitive);
    for (int i = 0; i <= sentence_a.length(); i++) {
        if (i == sentence_a.length() || !isalpha(sentence_a[i]) && !isdigit(sentence_a[i])) {
            if (!cur.empty()) {
                sort(cur.begin(), cur.end());
                if (word_counts_b.find(cur) != word_counts_b.end()) {
                    if (--word_counts_b[cur] == 0) word_counts_b.erase(cur);
                    cur = "";
                }
                else return false;
            }
            if (i == sentence_a.length()) break;
        }
        else if (is_case_sensitive) cur += sentence_a[i];
        else cur += tolower(sentence_a[i]);
    }
    return word_counts_b.empty();
}

int main() {
    std::string sentence_a, sentence_b;
    getline(std::cin, sentence_a);
    getline(std::cin, sentence_b);
    bool is_case_sensitive;
    std::cin >> is_case_sensitive;
    std::cout << is_anagram(sentence_a, sentence_b, is_case_sensitive) << std::endl;
    return 0;
}
