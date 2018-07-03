#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

/*Set value false for all tiles which belong current island.
Used DFS algorithm.
In this function map is not empty*/
void clear_this_island(vector<vector<bool> > &helper_map, int w, int h) {
    int width = helper_map[0].size();
    int height = helper_map.size();
    int add[4][2];//array to go to the next part of island
    add[0][0] = -1; add[0][1] = 0;
    add[1][0] = 0; add[1][1] = 1;
    add[2][0] = 1; add[2][1] = 0;
    add[3][0] = 0; add[3][1] = -1;
    helper_map[h][w] = false;
    for (int i = 0; i < 4; i++) {
        int new_w = w + add[i][0];
        int new_h = h + add[i][1];
        if (new_w < 0 || new_w >= width)
            continue;
        if (new_h < 0 || new_h >= height)
            continue;
        if (helper_map[new_h][new_w]) {
            clear_this_island(helper_map, w + add[i][0], h + add[i][1]);
        }
    }
}

/*Count number of islands by map*/
int count_islands(vector<vector<bool>> map) {
    int width = 0, height = 0;
    height = map.size();
    if (height != 0)
            width = map[0].size();
    int ans = 0;
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            if (map[h][w]) {
                clear_this_island(map, w, h);
                ans++;
            }
        }
    }
    return ans;
}

const bool T = true;//for more comfortable view tests

bool TEST_ASSERT_EQUAL_INT(int a, int b) {
    return a == b;
}

int main () {
    vector<vector<bool>> zero_map = {   {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0}};

    if (!TEST_ASSERT_EQUAL_INT(count_islands(zero_map), 0))
            cout << "Test zero failed\n";
    vector<vector<bool>> map = {{0, T, 0, T},
                                {T, T, 0, 0},
                                {0, 0, T, 0},
                                {0, 0, T, 0}};

    if (!TEST_ASSERT_EQUAL_INT(count_islands(map), 3))
            cout << "Test 1 failed\n";

    vector<vector<bool>> map2 = {   {T, 0, T, 0, T, 0},
                                    {0, T, 0, T, 0, T},
                                    {T, 0, T, 0, T, 0},
                                    {0, T, 0, T, 0, T},
                                    {T, 0, T, 0, T, 0},
                                    {0, T, 0, T, 0, T},
                                    {T, 0, T, 0, T, 0}};
    if (!TEST_ASSERT_EQUAL_INT(count_islands(map2), 21))
            cout << "Test 2 failed\n";
    vector<vector<bool>> map3 = {   {T, T, T, T, T, T},
                                    {T, T, 0, T, 0, T},
                                    {T, 0, T, 0, T, T},
                                    {T, T, 0, T, 0, T},
                                    {T, 0, T, 0, T, T},
                                    {T, T, 0, T, 0, T},
                                    {T, T, T, T, T, T}};
    if (!TEST_ASSERT_EQUAL_INT(count_islands(map3), 4))
            cout << "Test 3 failed\n";

    return 0;
}
