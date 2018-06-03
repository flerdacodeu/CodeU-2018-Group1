#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <string.h>
#include <climits>

namespace {
    const int ALFA_LEN = 26;
}

// Returns true if there is a path from source 's' to sink 't' in
// residual graph. Also fills parent[] to store the path */
bool bfs(std::vector<std::vector<int> > &rGraph, int s, int t, std::vector<int> &parent) {
    int graphSize = rGraph.size();
    std::vector<bool> visited(graphSize, false);
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < graphSize; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns the maximum flow from s to t in the given graph
int fordFulkerson(std::vector<std::vector<int> > &graph, int s, int t)
{
    int u, v, graphSize = graph.size();
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    std::vector<std::vector<int> > rGraph(graphSize, std::vector<int>(graphSize));
    
    // Residual graph where rGraph[i][j] indicates 
    // residual capacity of edge from i to j (if there
    // is an edge. If rGraph[i][j] is 0, then there is not)  

    for (u = 0; u < graphSize; u++)
        for (v = 0; v < graphSize; v++)
             rGraph[u][v] = graph[u][v];

    // This array is filled by BFS and to store path
    std::vector<int> parent(graphSize);
    // There is no flow initially
    int maxFlow = 0;
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = std::min(pathFlow, rGraph[u][v]);
        }
 
        // Update residual capacities of the edges and reverse edges
        // along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
 
        // Add path flow to overall flow
        maxFlow += pathFlow;
    }
 
    // Return the overall flow
    return maxFlow;
}

// Checks if two given words are anagrams (case sensitive)
bool areAnagrams(std::string initial, std::string anagram) {
    // If the words have different lengths, they can't be
    // anagrams
    if (anagram.size() != initial.size()) {
        return false;
    }

    // Vector of frequencies for each letter in the English
    // alphabet, lowercase (first ALFA_LEN elements) and
    // uppercase (last ALFA_LEN elements)
    std::vector<int> frequencies(ALFA_LEN  * 2);

    // Calculate frequencies for letters in the initial word
    for (char c : initial) {
        if (c >= 'A' && c <= 'Z')
            frequencies[c - 'A' + ALFA_LEN] ++;
        else
            frequencies[c - 'a'] ++;
    }

    // Check if the letter frequencies are the same in the
    // supposed anagram word
    for (char c : anagram) {
        if (c >= 'A' && c <= 'Z') {
            if (frequencies[c - 'A' + ALFA_LEN] == 0) {
                return false;
            }

            frequencies[c - 'A' + ALFA_LEN] --;
        } else {
            if (frequencies[c - 'a'] == 0) {
                return false;
            }

            frequencies[c - 'a'] --;
        }
    }

    return true;
}


bool verifyAnagram(std::string initial, std::string anagram) {
    // The words in each sentence
    std::vector<std::string> initialWords;
    std::vector<std::string> anagramWords;

    // Tokens for separating words
    std::string delim = " ,.!?\t\n\v\f\r";

    // Tokenize sentences into words using strtok
    char *initialStr = (char *)initial.c_str();
    char *token = strtok(initialStr, delim.c_str());

    while (token != nullptr) {
        initialWords.push_back(std::string(token));
        token = strtok(nullptr, delim.c_str());
    }

    char *anagramStr = (char *)anagram.c_str();
    token = strtok(anagramStr, delim.c_str());

    while (token != nullptr) {
        anagramWords.push_back(std::string(token));
        token = strtok(nullptr, delim.c_str());
    }

    // If the sentences have different numbers of words,
    // they can't be anagrams
    if (initialWords.size() != anagramWords.size()) {
        return false;
    }

    // Save word count for efficiency (avoids calling the size
    // function many times)
    int wordCnt = initialWords.size();

    // The first node represents the source
    // The next wordCnt nodes correspond to the words in the first sentence
    // The next wordCnt nodes correspond to the words in the second sentence
    // The last node represents the destionation
    std::vector<std::vector<int> > graph(wordCnt * 2 + 2, std::vector<int>(wordCnt * 2 + 2));

    // Set an outward edge from the source to every first sentence node
    // Set an outward esge from every second sentence node to the destination
    for (int i = 0; i < wordCnt; i ++) {
        graph[0][i + 1] = 1;
        graph[wordCnt + i + 1][wordCnt * 2 + 1] = 1;
    }

    // For every pair of word from the first sentence - word from the second
    // sentence, connect their respective nodes if they are anagrams
    for (int i = 0; i < wordCnt; i ++) {
        for (int j = 0; j < wordCnt; j ++) {
            if (areAnagrams(initialWords[i], anagramWords[j])) {
                graph[i + 1][wordCnt + j + 1] = 1;
            }
        }
    }

    // Calculate maximum flow through the constructed graph
    int maxFlow = fordFulkerson(graph, 0, wordCnt * 2 + 1);

    // Due to the way the graph was constructed, if the maximum flow is equal
    // to the number of words, it means that for every word in the second
    // sentence, there is an anagram word in the first sentence
    return maxFlow == wordCnt;
}
