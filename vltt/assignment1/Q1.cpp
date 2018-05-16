#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//ch == 0 -  sensitive, ch == 1 - insensitive

void to_sent(string &s, vector<string> &v, bool ch) {
    string cur;
    for (auto it : s) {
        if (isspace(it)) {
            if (!cur.empty()) {
                sort(cur.begin(), cur.end());
                v.push_back(cur);
                cur = "";
            }
        } 
        else if (ch) cur += tolower(it);
        else cur += it;
    }
    if (!cur.empty()) {
        sort(cur.begin(), cur.end());
        v.push_back(cur);
    }
}

bool sentence(string &a, string &b, bool ch) {
    vector<string> v_a, v_b;
    to_sent(a, v_a, ch);
    to_sent(b, v_b, ch);
    if (v_a.size() != v_b.size()) return false;
    sort(v_a.begin(), v_a.end());
    sort(v_b.begin(), v_b.end());
    return v_a == v_b;
}

bool word(string &a, string &b, bool ch) {
    if (a.length() != b.length()) return false;
    unordered_map<char, int> m;
    for (auto it : a) {
        if (ch) it = tolower(it);
        m[it]++;
    }
    for (auto it : b) {
        if (ch) it = tolower(it);
        if (m.find(it) != m.end()) {
            if (!m[it]) return false;
            m[it]--;
        }
        else return false;
    }
    return true;
}
