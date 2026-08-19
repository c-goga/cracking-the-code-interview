#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
    public:
    // two different marks for bidirectional search
    bool marked1; // forward mark
    bool marked2; // backward mark
    int data;

    Node() {
        marked1 = false;
        marked2 = false;
        data = 0;
    }

    Node(int d) {
        marked1 = false;
        marked2 = false;
        data = d;
    }
};

// directed graph
class Graph {
    private:
    map<Node*, list<Node*>> adjList; // adjaceny list to stoe the graph

    public:
    // add an edge between vertices u and v
    void addEdge(Node* u, Node* v) {
        // add edge from u to v, only u to v since directed
        adjList[u].push_back(v);
    }

    // print the adjacency list respresentation of the graph
    void print() {
        for (auto i: adjList) {
            cout << i.first->data << " -> ";
            for (auto j: i.second) {
                cout << j->data << " ";
            }
            cout << endl;
        }
    }

    // bidirectional search
    bool checkRoute(Node* s, Node* e) {
        s->marked1 = true;
        e->marked2 = true; 
        queue<Node *> q1; // need two seperate queues, one forward and one backward
        queue<Node *> q2;
        q1.push(s);
        q2.push(e);
        while(!q1.empty() || !q2.empty()) {
            if (!q1.empty()) {
                Node* r = q1.front();
                q1.pop();
                for (Node* n : adjList[r]) {
                    if (n->marked2 == true) { // if backwards bfs already found it, return true
                        return true;
                    } else if (n->marked1 == false) {
                        n->marked1 = true;
                        q1.push(n);
                    }
                }
            }

            if (!q2.empty()) {
                Node* r = q2.front();
                q2.pop();
                for (auto i: adjList) { // since we have to work backword, unfortunately we have to search the list everytime
                    if (i.first->marked2 == true) {
                        continue;
                    }

                    auto n = find(i.second.begin(), i.second.end(), r);
                    if (n != i.second.end()) {
                        if (i.first->marked1 == true) { // if forwards bfs already found it, return true
                            return true;
                        } else if (i.first->marked2 == false) {
                            q2.push(i.first);
                            i.first->marked2 == true;
                        }
                    }
                }
            }
        }
        
        return false;
    }

    void resetMarked() {
        for (auto i : adjList) {
            i.first->marked1 = false;
            i.first->marked2 = false;
        }
    }
};

int main() {
    Graph g;
    Node* s = new Node(1);
    Node* a = new Node(2);
    Node* b = new Node(3);
    Node* c = new Node(4);
    Node* e = new Node(5);
    g.addEdge(s, b);
    g.addEdge(b, s);
    g.addEdge(b, a);
    g.addEdge(b, c);
    g.addEdge(e, c);
    cout << boolalpha << g.checkRoute(s, e) << endl; // false
    g.resetMarked();
    g.addEdge(a, e);
    cout << boolalpha << g.checkRoute(s, e) << endl; // true
    return 0;
}

