#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <random>

using namespace std;

class BST {
    // idk why i decided to implement using an array this was way harder and didn't give me the optimal solution...
    private:
    int capacity;
    int size;
    vector<optional<int>> tree;
    vector<int> nodes;

    // helper method for treeify
    vector<int> copySubtree(int i) {
        if (i >= capacity) return {};
        if (!tree.at(i).has_value()) return {};

        vector<int> copy;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int d = q.front();
            q.pop();
            copy.push_back(tree.at(d).value());
            tree.at(d).reset(); // resets nodes as they are visited to not leave behind any detached nodes when we later reinsert them
            if (d*2+1 < capacity && tree.at(d * 2 + 1).has_value()) q.push(d*2+1);
            if (d*2+2 < capacity && tree.at(d * 2 + 2).has_value()) q.push(d*2+2);
        }
        return copy;
    }

    // helper method for delete
    void treeify(int i) {
        if (i >= capacity || !tree.at(i).has_value()) return;

        int left = i * 2 + 1;
        int right = i * 2 + 2;
        tree.at(i).reset();
        if (tree.at(left).has_value() && tree.at(right).has_value()) {
            vector<int> copyLeft = copySubtree(left);
            vector<int> copyRight = copySubtree(right);
            // reinserts all the nodes again starting at the left subtree then the right subtree
            // there should be a more efficient way honestly
            // if this were nodes this would be a lot easier
            for (int d: copyLeft) {
                insert(d);
            }
            for (int d: copyRight) {
                insert(d);
            }
        }
    }


    public:
    BST() {
        capacity = 1;
        tree.resize(capacity);
    }

    void print() {
        for (int i = 0; i < tree.size(); i++) {
            if (!tree.at(i).has_value()) {
                cout << "X ";
            } else {
                cout << tree.at(i).value() << " ";
            }
        }
        cout << endl;
    }
    
    void insert(int d) {
        int idx = 0; // start at the root
        while (tree.at(idx).has_value()) { // if current node is not null
            if (d <= tree.at(idx).value()) { // if d is <= current node
                idx = idx * 2 + 1; // go to the left
            } else { // if d > current node
                idx = idx * 2 + 2; // go to the right
            }

            if (idx >= capacity) { // if index goes past the current capacity, increase it
                capacity = capacity * 2 + 1;
                tree.resize(capacity);
            }
        }


        tree.at(idx) = d; // place element in spot found within tree
        nodes.push_back(d); // push element onto nodes vector to use later for getRandomNode
    }

    bool find(int d) {
        int idx = 0; // start at the root
        // keep looking until index goes over capacity, null is found, or d is found
        while (idx < capacity && tree.at(idx).has_value() && tree.at(idx).value() != d) { 
            if (d <= tree.at(idx).value()) { // if d is <= current node
                idx = idx * 2 + 1; // go to the left
            } else { // if d > current node
                idx = idx * 2 + 2; // go to the right
            }
        }
        
        if (idx >= capacity) return false; // index went over capacity so false

        return tree.at(idx).has_value(); // if has value then d was found, if no value d was not found and at null 
    }

    // can't use delete cause of C++...
    void del(int d) {
        int idx = 0; // start at the root
        // keep looking until index goes over capacity, null is found, or d is found
        while (idx < capacity && tree.at(idx).has_value() && tree.at(idx).value() != d) { 
            if (d <= tree.at(idx).value()) { // if d is <= current node
                idx = idx * 2 + 1; // go to the left
            } else { // if d > current node
                idx = idx * 2 + 2; // go to the right
            }
        }
        
        if (idx < capacity && tree.at(idx).has_value()) { // if element found then use helper method to delete it
            for(int i = 0; i < nodes.size(); i++) {
                if (nodes.at(i) == tree.at(idx).value()) { // O(n) time on deletion cause of random... ahhh
                    nodes.erase(nodes.begin() + i);
                    break;
                }
            }
            treeify(idx);
        }
    }

    int getRandomNode() {
        random_device rd; // random seed from hardware
        mt19937 gen(rd()); // initialize standard Mersenne Twister engine with seed, based on mersenne twister algorithm
        uniform_int_distribution<int> disturn(0, nodes.size()); // define the range
        return nodes.at(disturn(gen)); // generate the number
    }
};


int main() {
    BST b;
    b.insert(5);
    b.insert(8);
    b.insert(11);
    b.insert(9);
    b.insert(10);
    b.insert(12);
    b.print();
    cout << boolalpha << "true: " << b.find(5) << endl;
    cout << boolalpha << "false: " << b.find(13) << endl;
    b.del(11);
    b.print();
    cout << "rand: " << b.getRandomNode() << endl; // 5, 8, 9, 10, or 12
    return 0;
}