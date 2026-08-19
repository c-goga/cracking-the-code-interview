#include <iostream>

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

};

class Successor {
    public:
    // returns nullptr if no successor is found
    TreeNode* successor(TreeNode* n) {
        if (n->right) return n->right;

        TreeNode* p = n->parent;
        while (n->parent && p->right == n) {
            n = p;
            p = n->parent;
        }

        return n->parent;
    }
};

int main() {
    TreeNode* root = new TreeNode(9);
    root->addChild(2);
    root->addChild(11);
    root->addChild(1);
    root->addChild(5);

    /**
     * Tree Representation:
     * 
     *          9
     *       2    11
           1   5
     * 
     */

    Successor s;
    root->print(); // 1 2 5 9 11, in order list for reference
    cout << s.successor(root->left)->d << endl; // 5
    cout << s.successor(root->left->left)->d << endl; // 2
    cout << s.successor(root->left->right)->d << endl; // 9
    cout << (s.successor(root->right) == nullptr ? "NULL" : "FAILED") << endl; // NULL
    return 0;
}