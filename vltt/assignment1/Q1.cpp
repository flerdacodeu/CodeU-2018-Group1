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

bool f(string &a, string &b, bool ch) {
    vector<string> v_a, v_b;
    to_sent(a, v_a, ch);
    to_sent(b, v_b, ch);
    if (v_a.size() != v_b.size()) return false;
    sort(v_a.begin(), v_a.end());
    sort(v_b.begin(), v_b.end());
    return v_a == v_b;
}

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    bool ch;
    cin >> ch;
    cout << f(a, b, ch) << endl;
    return 0;
}
