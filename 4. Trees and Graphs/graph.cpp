// geeksforgeeks implementation of a graph

#include <iostream>
#include <list>
#include <map>
using namespace std;

// directed
class Graph {
    map<int, list<int>> adjList; // adjaceny list to stoe the graph

    public:
    // add an edge between vertices u and v
    void addEdge(int u, int v) {
        // add edge from u to v, only u to v since directed
        adjList[u].push_back(v);
    }

    // print the adjacency list respresentation of the graph
    void print() {
        for (auto i: adjList) {
            cout << i.first << " -> ";
            for (auto j: i.second) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};