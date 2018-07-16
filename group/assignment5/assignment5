#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <memory>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <deque>
#include <unordered_set>
#include <stack>
#include <functional>

using namespace std;


void dfs(char cur_vertx,
         map <char, vector <char> > &graph,
         map <char, int> &used,
         vector <char> &ans,
         bool &find_cycle) {

    used[cur_vertx] = 1;
    for (auto it :graph[cur_vertx]) {
        if (used[it] == 1) {
            find_cycle = 1;
        }
        else if (used[it] == 0) {
            dfs(it,graph, used, ans, find_cycle);
        }
    }
    used[cur_vertx] = 2;
    ans.push_back(cur_vertx);
}

vector <char> top_sort(map <char, vector <char> > &graph, bool &find_cycle) {
    vector <char> ans;
    map <char, int> used;
    for (auto it :graph) {
        if (used[it.first] == 0) {
            dfs(it.first,graph, used, ans, find_cycle);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

pair <char, char> find_diff(string &f, string &s) {
    for (int i = 0; i < min(f.size(), s.size()); ++i) {
        if (f[i] != s[i]) {
            return make_pair(f[i], s[i]);
        }
    }
    return make_pair('-', '-');
}

//compare adjacent rows and build a graph
vector <char> solve(vector <string> &dict, bool &success) {
    map <char, vector <char> >graph;
    for (int i = 0; i < int(dict.size()) - 1; ++i) {
        pair <char, char> diff = find_diff(dict[i], dict[i + 1]);
        if (diff.first != diff.second) {
           graph[diff.first].push_back(diff.second);
        }
    }
    bool find_cycle = 0;
    vector <char> ans = top_sort(graph, find_cycle);
    success = !find_cycle;
    return ans;
}

int main() {
    int nmbr_of_words;
    cin >> nmbr_of_words;
    vector <string> dict(nmbr_of_words);
    for (int i = 0; i <nmbr_of_words; ++i) {
        cin >> dict[i];
    }
    bool success;
    vector <char> ans = solve(dict, success);
    if (success) {
        cout << "Alphabet found:" << endl;
        for (auto it : ans) cout << it;
        cout << endl;
    }
    else {
        cout << "There is no alphabet for this dictionary" << endl;
    }
}
