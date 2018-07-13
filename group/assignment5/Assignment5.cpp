#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <vector>

std::map<char, std::vector<char>> BuildGraph(const std::vector<string> &dictionary) {
    std::map<char,std::vector<char>> graph;
    for (int i = 1; i < dictionary.size(); i++) {
        for (int j = 0; j < min(dictionary[i].size(), dictionary[i-1].size()); j++) {
            if (dictionary[i][j] != dictionary[i-1][j]) {
                graph[dictionary[i-1][j]].push_back(dictionary[i][j]);
                break;
            }
        }
    }
    return graph;
}

std::map<char, int> GetIndegreeVertex(const std::map<char, std::vector<char>> &graph) {
    std::map<char, int> indegree;
    for (auto &map_node: graph) {
        const std::vector<char> &neighbours = map_node.second;
        for (char neighbour: neighbours) {
            indegree[neighbour]++;
        }
    }
    return indegree;
}

std::vector<char> FindAlphabetOrder(const std::vector<string> &dictionary) {
    auto graph = BuildGraph(dictionary);
    auto indegree = GetIndegreeVertex(graph);

    std::queue<char> bfs_queue;
    for(auto v: indegree) {
        char vertex = v.first;
        char vertex_indegree = v.second;
        if(vertex_indegree == 0) {
            bfs_queue.push(vertex);
        }
    }
    
    std::vector<char> alphabet_sorted;
    while (!bfs_queue.empty()) {
        char current = bfs_queue.front();
        alphabet_sorted.push_back(current);
        bfs_queue.pop();
        for (auto neighbour: graph[current]) {
            indegree[neighbour]--;
            if (indegree[neighbour] == 0) {
                bfs_queue.push(neighbour);
            }
        }
    }
    
    return alphabet_sorted;
}

int main() {
    return 0;
}
