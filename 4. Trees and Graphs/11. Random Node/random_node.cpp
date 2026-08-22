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
        uniform_int_distribution<int> disturn(0, nodes.size() - 1); // define the range
        return nodes.at(disturn(gen)); // generate the number
    }
};

// textbook implementation
class TreeNode {
    private:

    void inOrder(TreeNode* t) {
        if (t != nullptr) {
            inOrder(t->left);
            cout << t->data << " ";
            inOrder(t->right);
        }
    }

    public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int treeSize = 0;

    TreeNode(int d) {
        data = d;
        treeSize = 1;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    int size() { return treeSize; }

    TreeNode* getIthNode(int i) {
        int leftSize = left == nullptr ? 0 : left->size();
        
        if (i < leftSize) {
            return left->getIthNode(i);
        } else if (i == leftSize) {
            return this;
        } else {
            return right->getIthNode(i - (leftSize + 1)); // skipping over leftSize + 1 nodes, so subtract them
        }
    }

    void insertInOrder(int d) {
        if (d <= data) {
            if (left == nullptr) {
                left = new TreeNode(d);
                left->parent = this;
            } else {
                left->insertInOrder(d);
            }
        } else {
            if (right == nullptr) {
                right = new TreeNode(d);
                right->parent = this;
            } else {
                right->insertInOrder(d);
            }
        }
        treeSize++;
    }

    TreeNode* find(int d) {
        if (d == data) {
            return this;
        } else if (d <= data) {
            return left != nullptr ? left->find(d) : nullptr;
        } else if (d > data) {
            return right != nullptr ? right->find(d) : nullptr;
        }

        return nullptr;
    }

    void del(int d) {
        TreeNode* t = find(d);
        if (t == nullptr) return;

        // Case 1: a leaf
        if (t->left == nullptr && t->right == nullptr) {
            if (t->parent != nullptr) { // if not the root
                t->parent->left = t->parent->left == t ? nullptr : t->parent->left;
                t->parent->right = t->parent->right == t ? nullptr : t->parent->right;
            }
        // Case 2: two children
        } else if (t->left != nullptr && t->right != nullptr) {
            // can replace with rightmost child of left child or leftmost child of right child, we will be doing the former
            TreeNode* tmp = t->left;
            while (tmp->right != nullptr) {
                tmp = tmp->right;
            }

            if (t->parent != nullptr) { // if not the root
                t->parent->left = t->parent->left == t ? tmp : t->parent->left;
                t->parent->right = t->parent->right == t ? tmp : t->parent->right;
            }

            if (t->left != tmp) {
                tmp->parent->left = tmp->parent->left == tmp ? nullptr : tmp->parent->left;
                tmp->parent->right = tmp->parent->right == tmp ? nullptr : tmp->parent->right;
                tmp->left = t->left;
            } else {
                tmp->left = nullptr;
            }

            tmp->parent = t->parent;
            tmp->right = t->right;
            // cout << "TMP P: " << tmp->parent->data << endl;
            // cout << "TMP L: " << tmp->left->data << endl;
            // cout << "TMP R: " << tmp->right->data << endl;
        // Case 3: one child 
        } else if (t->left != nullptr || t->right != nullptr) {
            TreeNode* tmp = t->right == nullptr ? t->left : t->right;
            if (t->parent != nullptr) { // if not the root
                t->parent->left = t->parent->left == t ? tmp : t->parent->left;
                t->parent->right = t->parent->right == t ? tmp : t->parent->right;
            }
            tmp->parent = t->parent;
        }

        delete t;
    }

    void print() {
        inOrder(this);
        cout << endl;
    }
};

class Tree {
    public:
    TreeNode* root = nullptr;

    int size() { return root == nullptr ? 0 : root->size(); }

    TreeNode* getRandomNode() {
        if (root == nullptr) return nullptr;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(0, size() - 1);
        return root->getIthNode(distrib(gen));
    }

    void insertInOrder(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            root->insertInOrder(value);
        }
    }
};

// end of textbook implementation

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

    cout << endl << "Textbook: " << endl;
    Tree t;
    t.insertInOrder(5);
    t.insertInOrder(4);
    t.insertInOrder(8);
    t.insertInOrder(6);
    t.insertInOrder(11);
    t.insertInOrder(7);
    t.insertInOrder(10);
    t.insertInOrder(12);
    /**
     *              5
     *          4       8
     *              6        11
     *                 7  10    12
     */
    t.root->print(); // 4 5 6 7 8 10 11 12

    cout << "rand: " << t.getRandomNode()->data << endl; // one of the numebrs listed two lines above
    // Case 2: delete node with two children
    t.root->del(8);
    /**
     *              5
     *          4       7
     *              6        11
     *                    10    12
     */
    t.root->print(); // 4 5 6 7 10 11 12

    // Case 2: delete node with two children
    t.root->del(7);
    /**
     *              5
     *          4       6
     *                       11
     *                    10    12
     */
    t.root->print(); // 4 5 6 10 11 12

    // Case 1: delete leaf node
    t.root->del(12);
    /**
     *              5
     *          4       6
     *                       11
     *                    10    
     */
    t.root->print(); // 4 5 6 7 10 11 

    // Case 3: delete node with one child
    t.root->del(6);
    /**
     *              5
     *          4       11
     *               10     
     *                    
     */
    t.root->print(); // 4 5 10 11
    return 0;
}