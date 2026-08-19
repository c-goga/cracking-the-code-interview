#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

class TreeNode {
    private:
    void inOrder(TreeNode* n) {
        if (n) {
            inOrder(n->left);
            cout << n->d << " ";
            inOrder(n->right);
        }
    }

    public:
    int d;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int data) {
        d = data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void addChild(int d) {
        if (d <= this->d) {
            if (!left) {
                left = new TreeNode(d);
                left->parent = this;
            } else {
                left->addChild(d);
            }
        } else {
            if (!right) {
                right = new TreeNode(d);
                right->parent = this;
            } else {
                right->addChild(d);
            }
        }
    }

    void print() {
        inOrder(this);
        cout << endl;
    }

    TreeNode(vector<int> v) {
        if (v.empty()) return;

        d = v[0];
        for (int i = 1; i < v.size(); i++) {
            addChild(v[i]);
        }
    }

};

void print(vector<int> l) {
    for (int i : l) {
        cout << i << " ";
    }
    cout << endl;
}

class Sequence {
    private:
    vector<vector<int>> permutations(vector<int> l) {
        if (l.size() == 1) return {l}; // if only one element left return

        vector<vector<int>> p; // return value of all possible permutations
        for (int i = 0; i < l.size(); i++) { // double for loop of n where n is the size of the initial list
            vector<int> v1 = {l[i]}; // take one element away from the list
            vector<int> copy = l; // make a copy of the list 
            copy.erase(copy.begin() + i); // delete the element 
            vector<vector<int>> v2 = permutations(copy); // find permutations for list without the element chosen
            for (int j = 0; j < v2.size(); j++) { // for each permutation found join them with the element taken (which will be at the beginning)
                v1.insert(v1.end(), v2[j].begin(), v2[j].end());
                p.push_back(v1);
                v1 = {l[i]}; // reset v1 to only be the element taken again
            }
        }
        return p; // return all found permutations
    }

    vector<vector<int>> join(vector<int> l, vector<vector<vector<int>>> v) {
        if (v.empty()) {
            return {}; // base case, returns empty bracket
        } 

        // cout << "l: ";
        // print(l);

        vector<vector<int>> res; // return value
        vector<vector<int>> v2 = v[0]; // copy of first element since we will be deleting it in the next line and need it for the loop
        v.erase(v.begin()); // delete it so we can use it in the recursive call later
        for (int i = 0; i < v2.size(); i++) {
            vector<int> start = l; // copy the original list l
            start.insert(start.end(), v2[i].begin(), v2[i].end()); // create new start by joining the permutations together
            vector<vector<int>> tmp = join(start, v); // recursive call
            if (tmp.empty()) { // if empty, that means we have reached the end and can add it to the return field
                res.push_back(start);
            } else {
                res.insert(res.end(), tmp.begin(), tmp.end()); // if not empty, this means it is returning a list of permutations we 
                                                                // need to add to our list of perumtations (res)
            }
        }

        return res; // return all the list of permutations
    }
    
    public:
    vector<vector<int>> bstSequence(TreeNode* root) {
        vector<vector<int>> res; // return field
        vector<vector<int>> levels; // vector for every level found
        queue<TreeNode*> q; // queue for BST
        q.push(root);
        int level = 0; // to know where to add nodes within the levels vector
        int levelSize = 1; // to know how many nodes to add within an element in the levels vector
        while (!q.empty()) { 
            int stop = levelSize; // need a field for the for loop since levelSize will be changing before it and within it
            levelSize = 0; // reset levelSize
            levels.push_back({}); // push back an empty vector since we are starting a new level, if we don't do this then line 134 will fail
            for (int i = 0; i < stop; i++) {
                TreeNode* n = q.front();
                q.pop();

                levels[level].push_back(n->d); // push node onto specfic level

                if (n->left) { 
                    q.push(n->left);
                    levelSize++;
                }
                if (n->right) {
                    q.push(n->right);
                    levelSize++;
                }
            }
            level++;
        }
        vector<vector<vector<int>>> p;
        for (vector<int> l : levels) {
            p.push_back(permutations(l)); // get all the permutations for each of the levels
        }

        vector<vector<vector<int>>> copy(p.begin() + 1, p.end());
        res = join(p[0][0], copy); // join every single permutation together to get the sequences needed

        return res; // O(n^2 * d) time, where n is the number of nodes at each depth and d is the depth
                    // O(n^3) space, since we needed a 3D vector to hold all the permutation and join them
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->addChild(2);
    root->addChild(6);
    root->addChild(1);
    root->addChild(4);
    root->addChild(7);
    /**
     * Tree representation:
     * 
     *          3
     *      2       6
     *    1       4   7
     */

    Sequence s;
    cout << "Root: ";
    root->print(); // 1 2 3 4 6 7
    cout << endl << "Sequences: " << endl;
    vector<vector<int>> sequences = s.bstSequence(root);
    for (int i = 0; i < sequences.size(); i++) {
        for (int j = 0; j < sequences[i].size(); j++) {
            cout << sequences[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl<< "Trees: " << endl;
    for (int i = 0; i < sequences.size(); i++) {
        TreeNode* n = new TreeNode(sequences[i]);
        cout << (i + 1) << ": ";
        n->print(); // should all be 1 2 3 4 6 7
    }

    return 0;
}