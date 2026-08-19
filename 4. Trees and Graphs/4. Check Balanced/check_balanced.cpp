#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

class TreeNode {
    public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }

    void addChild(TreeNode* n) {
        if (n->data == data) return;

        queue<TreeNode*> q;
        q.push(this);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if(!curr->left) {
                curr->left = n;
                return;
            } else {
                q.push(curr->left);
            }

            if (!curr->right) {
                curr->right = n;
                return;
            } else {
                q.push(curr->right);
            }
        }
    }

    void addLeft(TreeNode* n) {
        if (!left) left = n;
    }
    
    void addRight(TreeNode* n) {
        if (!right) right = n;
    }
};

class Balanced {
    private:
    int getDepth(TreeNode* root) {
        if (root == nullptr) return 1;

        int left = getDepth(root->left);
        int right = getDepth(root->right);
        // cout << "n: " << root->data << endl;
        // cout << "l: " << left << endl;
        // cout << "r: " << right << endl;

        if (left == -1 || right == -1) return -1;

        if (abs(left - right) > 1) return -1;


        return max(left, right) + 1;
    }

    public:
    bool check(TreeNode* root) {
        if (getDepth(root) == -1) return false;
        return true;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    TreeNode* wrong = new TreeNode(4);
    left->addLeft(wrong);
    left->addRight(new TreeNode(5));
    root->addLeft(left);
    root->addRight(new TreeNode(3));
    Balanced b;
    cout << boolalpha << b.check(root) << endl; // true
    wrong->addLeft(new TreeNode(6)); // now unbalanced
    cout << boolalpha << b.check(root) << endl; // false;
    return 0;
}