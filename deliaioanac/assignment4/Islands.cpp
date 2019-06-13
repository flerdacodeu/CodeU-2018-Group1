#include <vector>
#include <iostream>
 
// Function that return the 'head' of the island patch i belongs to
int find(int i, std::vector<int> &parent) {
    int head = i, aux;
 
    while (head != parent[head]) {
        head = parent[head];
    }
 
    // Path compression (make the parent of every node along
    // the way to be the head of the whole island)
    while (i != parent[i]) {
        aux = parent[i];
        parent[i] = head;
        i = aux;
    }
 
    return head;
}

// Unite two islands
void unite(int i, int j, std::vector<int> &parent, std::vector<int> &rank) {
    if (rank[i] > rank[j]) {
        parent[j] = i;
    } else {
        parent[i] = j;
    }
 
    if (rank[i] == rank[j]){
        rank[j] ++;
    }
}

int countingIslands(const std::vector<std::vector<bool> > &map) {
    // If there is no map, there can be no islands
    if (map.empty()) {
        std::cout << "The map is empty!" << std::endl;
        return 0;
    }

    // The initial number of distinct possible patches of land
    int numberOfIslands = map.size() * map[0].size();
    std::vector<int> parent(numberOfIslands), rank(numberOfIslands);

    for (int i = 0; i < map.size(); i ++) {
        for (int j = 0; j < map[i].size(); j ++) {
            if (map[i][j]) {
                parent[i * map.size() + j] = i * map.size() + j;
                rank[i * map.size() + j] = 0;

                // Check if these is a patch of land above this one and,
                // if there is, unite its island to this patch of land
                if (i > 0 && map[i - 1][j]) {
                    unite(find(i * map.size() + j, parent),
                          find((i - 1) * map.size() + j, parent), parent, rank);
                    numberOfIslands --;
                }

                // Check if there is a patch of land to the left of this
                // one and, if there is and it does not belong to the
                // same island as a patch of land above, unite their islands
                if (j > 0 && map[i][j - 1] &&
                    (i == 0 || !map[i - 1][j] ||
                    find((i - 1) * map.size() + j, parent) !=
                    find(i * map.size() + (j - 1), parent))) {
                    unite(find(i * map.size() + j, parent),
                          find(i * map.size() + (j - 1), parent), parent, rank);
                    numberOfIslands --;
                }
            } else {
                // If it is not land, it cannot be an island
                numberOfIslands --;
            }
        }
    }
 
    return numberOfIslands;
}
