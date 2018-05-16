#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <unordered_map>

//is_case_insensitive == 0 -  sensitive, is_case_insensitive == 1 - insensitive

void split_by_word(std::string &s, std::unordered_map<std::string, int> &m, bool is_case_insensitive) {
    std::string cur;
    for (int i = 0; i <= s.length(); i++) {
        if (i == s.length() || isspace(s[i])) {
            if (!cur.empty()) {
                sort(cur.begin(), cur.end());
                m[cur]++;
                cur = "";
            }
            if (i == s.length()) return;
        } 
        else if (is_case_insensitive) cur += tolower(s[i]);
        else cur += s[i];
    }
}

bool is_anagram(std::string &a, std::string &b, bool ch) {
    std::unordered_map<std::string, int> m_b;
    std::string cur;
    split_by_word(b, m_b, is_case_insensitive);
    for (int i = 0; i <= a.length(); i++) {
        if (i == a.length() || isspace(a[i])) {
            if (!cur.empty()) {
                sort(cur.begin(), cur.end());
                if (m_b.find(cur) != m_b.end()) {
                    if (--m_b[cur] == 0) m_b.erase(cur);
                    cur = "";
                }
                else return false;
            }
            if (i == a.length()) break;
        }
        else if (is_case_insensitive) cur += tolower(a[i]);
        else cur += a[i];
    }
    return m_b.empty();
}

int main() {
    std::string a, b;
    getline(std::cin, a);
    getline(srd::cin, b);
    bool ch;
    std::cin >> ch;
    std::cout << f(a, b, ch) << std::endl;
    return 0;
}
