#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class TreeNode {
    private:
    void inOrder(TreeNode* n) {
        if (n != nullptr) {
            inOrder(n->left);
            cout << n->d << " ";
            inOrder(n->right);
        }
    }

    public:
    int d;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        this->d = d;
        left = nullptr;
        right = nullptr;
    }

    void addChild(TreeNode* n) {
        if (n->d == d) return;

        if (n->d < d) {
            if (!left) left = n;
            else left->addChild(n);
        } else {
            if (!right) right = n;
            else right->addChild(n);
        }
    }

    void print() {
        inOrder(this);
        cout << endl;
    }
};

void print(vector<int> l) {
    for (int i : l) {
        cout << i << " ";
    }
    cout << endl;
}

class MinTree {
    public:
    TreeNode* minTree(vector<int> l) {
        int pivot = l.size() / 2;
        TreeNode* root = new TreeNode(l[pivot]);
        if (pivot > 0) root->addChild(minTree(vector<int> (l.begin(), l.begin() + (pivot))));
        if (pivot + 1 < l.size()) root->addChild(minTree(vector<int> (l.begin() + (pivot + 1), l.end())));
        return root;
    }
};

int main() {
    vector<int> l = {1, 2, 3, 5, 10};
    MinTree t;
    TreeNode* n = t.minTree(l);
    n->print();
}