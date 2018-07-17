#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cerr;
using std::string;
using std::vector;
using std::min;

struct Vertex {
    char curChar;
    int color = 0; //need for top sort with DFS
    vector<Vertex *> charsMore;
    vector<Vertex *> charsLess;
};

bool topSort(Vertex & cur, vector<char> & resAlphabet) {
    cur.color = 1;
    for (int i = 0; i < cur.charsLess.size(); i++) {
        if ((*cur.charsLess[i]).color == 0) {
            if (!topSort(*cur.charsLess[i], resAlphabet))
                return false;
        }
        else if ((*cur.charsLess[i]).color == 1) {
            return false;
        }
    }
    cur.color = 2;
    resAlphabet.push_back(cur.curChar);
    return true;
}

void setOrder(Vertex & less, Vertex & more) {
    less.charsMore.push_back(&more);
    more.charsLess.push_back(&less);
}

//number of first different letter if it perhaps, otherwise return min of length
int minDiff (const string a, const string b) {
    int minSize = min(a.size(), b.size());
    int curLet = 0;
    while (curLet < minSize && a[curLet] == b[curLet]) {
        curLet++;
    }
    return curLet;
}

//return true if input is correct order is perhaps
//put alphabet own of posible alphabets, if it's perhaps
bool setInAlpOrd(vector<char> & resAlphabet, vector<string> & dict) {
    const int ALPSIZE = 256;
    Vertex order[ALPSIZE];
    for (int i = 0; i < ALPSIZE; i++) {
        order[i].curChar = char(i);
    }
    int dictSize = dict.size();
    for (int numOfWorld = 0; numOfWorld < (dictSize - 1); numOfWorld++) {
        string one = dict[numOfWorld];
        string two = dict[numOfWorld + 1];
        int minNEqLet = minDiff(one, two);
        int minSize = min(one.size(), two.size());
        if (minSize > minNEqLet) {
            setOrder(order[one[minNEqLet]], order[two[minNEqLet]]);
        }
    }
    for (int i = 0; i < ALPSIZE; i++) {
        if (!topSort(order[i], resAlphabet)) {
            resAlphabet.resize(0);
            cerr << "Incorrect input";
            return false;
        }
    }
    return true;
}

int main() {
    return 0;
}
